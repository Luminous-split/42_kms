#include <mlx.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 1000
#define HEIGHT 800
#define SCALE 10

typedef struct s_point {
    float x, y, z;
} t_point;

typedef struct s_img {
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
} t_img;

typedef struct s_vars {
    void *mlx;
    void *win;
    t_img img;
    int **map;
    int width;
    int height;
    int x_offset;
    int y_offset;
    float scale;
    float current_angle;
    int is_mouse_pressed;
    int prev_mouse_pos;
	int r_clicked;

    float center_x;
    float center_y;
} t_vars;

void print_progress(int current, int total)
{
    static int last_percent = -1;
    int percent = (current * 100) / total;

    // Only print if percent has increased to avoid spamming
    if (percent != last_percent)
    {
        printf("\rRendering: %d%%", percent);
        fflush(stdout);
        last_percent = percent;
    }
}

// --------- Drawing ---------
void put_pixel(t_img *img, int x, int y, int color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    char *dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

void draw_line(t_vars *v, t_point a, t_point b, int color) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    int steps = fmax(fabs(dx), fabs(dy));
    float x_inc = dx / steps;
    float y_inc = dy / steps;
    float x = a.x;
    float y = a.y;
    for (int i = 0; i <= steps; i++) {
        put_pixel(&v->img, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
    }
}

t_point project(int x, int y, int z, t_vars *v) {
    t_point p;

    float centered_x = x - v->center_x;
    float centered_y = y - v->center_y;

    float rot_x = centered_x * cos(v->current_angle) - centered_y * sin(v->current_angle);
    float rot_y = centered_x * sin(v->current_angle) + centered_y * cos(v->current_angle);

//    float xx = (rot_x - rot_y) * cos(0.523599);
//    float yy = (rot_x + rot_y) * sin(0.523599) - z;
    float xx = rot_x;
    float yy = rot_y - z;

    p.x = xx * v->scale + WIDTH / 2 + v->x_offset;
    p.y = yy * v->scale + HEIGHT / 2 + v->y_offset;
    return p;
}

void draw_map(t_vars *v) {
	int total = v->width * v->height;
	int current = 0;

     if (v->img.img)
         mlx_destroy_image(v->mlx, v->img.img);

     v->img.img = mlx_new_image(v->mlx, WIDTH, HEIGHT);
     v->img.addr = mlx_get_data_addr(v->img.img, &v->img.bpp, &v->img.line_len, &v->img.endian);
     for (int y = 0; y < v->height; y++) {
         for (int x = 0; x < v->width; x++) {
             int z = v->map[y][x];
             t_point p = project(x, y, z, v);
             if (x + 1 < v->width)
                 draw_line(v, p, project(x + 1, y, v->map[y][x + 1], v), 0xFFFF00);
             if (y + 1 < v->height)
                 draw_line(v, p, project(x, y + 1, v->map[y + 1][x], v), 0xFFFF00);
	     print_progress(current, total);
	     current++;
        }
     }
     mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
}

t_point **realloc_map(t_point **old, t_point *new_row, int new_size)
{
    t_point **new_map = malloc(sizeof(t_point *) * new_size);
    for (int i = 0; i < new_size - 1; i++)
        new_map[i] = old[i];
    new_map[new_size - 1] = new_row;
    free(old);
    return new_map;
}

void free_split(char **arr)
{
    int i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

int **parse_map(const char *filename, int *width, int *height) {
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return NULL;

    int row_capacity = 128;
    int **map = malloc(sizeof(int *) * row_capacity);
    if (!map) {
        fclose(fp);
        return NULL;
    }

    char line[4096];
    *width = 0;
    int row = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (row >= row_capacity) {
            row_capacity *= 2;
            int **tmp = realloc(map, sizeof(int *) * row_capacity);
            if (!tmp) {
                // Free previous allocations before returning
                for (int i = 0; i < row; i++)
                    free(map[i]);
                free(map);
                fclose(fp);
                return NULL;
            }
            map = tmp;
        }

        // Count columns in this line
        int col_capacity = 16;
        int *cols = malloc(sizeof(int) * col_capacity);
        if (!cols) {
            for (int i = 0; i < row; i++)
                free(map[i]);
            free(map);
            fclose(fp);
            return NULL;
        }

        int col = 0;
        char *token = strtok(line, " \n");
        while (token) {
            if (col >= col_capacity) {
                col_capacity *= 2;
                int *tmp_cols = realloc(cols, sizeof(int) * col_capacity);
                if (!tmp_cols) {
                    free(cols);
                    for (int i = 0; i < row; i++)
                        free(map[i]);
                    free(map);
                    fclose(fp);
                    return NULL;
                }
                cols = tmp_cols;
            }
            cols[col++] = atoi(token);
            token = strtok(NULL, " \n");
        }

        map[row++] = cols;
        if (col > *width)
            *width = col;
    }

    *height = row;
    fclose(fp);
    return map;
}

int mouse_pressed(int button, int x, int y, t_vars *v) {
    if (button == 1) { // Left click
        v->is_mouse_pressed = 1;
        v->prev_mouse_pos = x;
    }
    return 0;
}

int mouse_released(int button, int x, int y, t_vars *v) {
    if (button == 1)
        v->is_mouse_pressed = 0;
    return 0;
}

int mouse_move(int x, int y, t_vars *v) {
    (void)y; // not using vertical movement

    if (v->is_mouse_pressed) {
        int dx = x - v->prev_mouse_pos;
        v->current_angle += dx * 0.09; // adjust speed if needed
        v->prev_mouse_pos = x;

        draw_map(v);
    }
    return 0;
}

int handle_key(int keycode, t_vars *v) {
    if (keycode == 0xff1b) // ESC
        exit(0);
    if (keycode == 0x3d) // +
        v->scale += 2;
    if (keycode == 0x2d) // -
        v->scale -= 2;
    if (keycode == 0xff51) // left
        v->x_offset -= 20;
    if (keycode == 0xff53) // right
        v->x_offset += 20;
    if (keycode == 0xff52) // up
        v->y_offset -= 20;
    if (keycode == 0xff54) // down
        v->y_offset += 20;
    if (keycode == 0x72) // down
        v->r_clicked = !v->r_clicked;

    draw_map(v);
    return 0;
}

int auto_rotate(t_vars *v) {

	if (v->r_clicked)
	{
		v->current_angle += 0.01;
		draw_map(v);
	}
	return 0;
}

// --------- Main ---------
int main(int argc, char **argv) {
    if (argc != 2) {
        write(2, "Usage: ./fdf 42map.fdf\n", 24);
        return 1;
    }

    t_vars v;
    v.width = 0;
    v.height = 0;
    v.x_offset = 0;
    v.y_offset = 0;
    v.scale = 20.0;
    v.current_angle = 0;
    v.is_mouse_pressed = 0;
    v.prev_mouse_pos = 0;
    v.r_clicked = 0;

    v.map = parse_map(argv[1], &v.width, &v.height);
    if (!v.map) {
        write(2, "Error: Failed to load map\n", 26);
        return 1;
    }
    v.center_x = (float)v.width / 2;
    v.center_y = (float)v.height / 2;

    v.mlx = mlx_init();
    v.win = mlx_new_window(v.mlx, WIDTH, HEIGHT, "42 FDF");
    v.img.img = mlx_new_image(v.mlx, WIDTH, HEIGHT);
    v.img.addr = mlx_get_data_addr(v.img.img, &v.img.bpp, &v.img.line_len, &v.img.endian);

    draw_map(&v);
    mlx_key_hook(v.win, handle_key, &v);

    mlx_mouse_hook(v.win, mouse_pressed, &v);
    mlx_hook(v.win, 6, 1L << 6, mouse_move, &v);         // Mouse move
    mlx_hook(v.win, 5, 1L << 3, mouse_released, &v);           // Mouse release
    mlx_loop_hook(v.mlx, auto_rotate, &v);
    mlx_loop(v.mlx);
    return 0;
}
