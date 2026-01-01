NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -Llibft -lft

SRCS = pipex.c pipex_exec_cmd.c pipex_utils.c pipex_utils_1.c

OBJS = $(SRCS:.c=.o)

BONUS_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c pipex_bonus.c pipex_exec_cmd_bonus.c pipex_utils_bonus.c pipex_utils_1_bonus.c pipex_utils_2_bonus.c

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: lftall $(NAME) clean

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

bonus: $(BONUS_OBJS) lftall
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(INCLUDES) -o $(NAME)

clean: lftclean
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean lftfclean
	rm -f $(NAME)

re: fclean all

lftall:
	$(MAKE) -C libft all

lftclean:
	$(MAKE) -C libft clean

lftfclean:
	$(MAKE) -C libft fclean

.PHONY: all clean fclean re
