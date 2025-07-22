NAME = push_swap

CC = cc

CFLAGS = -Wall -Werror -Wextra -g 

INCLUDES = -Llibft -lft

SRCS = push_swap.c parse.c linkedlist_utils.c instructions_a.c instructions_b.c instructions_both.c sort.c indice.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: lftall $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

lftall:
	$(MAKE) -C libft all

lftclean:
	$(MAKE) -C libft clean

lftfclean:
	$(MAKE) -C libft fclean

.PHONY: all clean fclean re

