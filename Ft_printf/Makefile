NAME := libftprintf.a

CFLAGS := -Wall -Werror -Wextra

RM := rm -rf

CC := cc

SRCS := ft_printf.c srcs/ft_printchar.c srcs/ft_printchex.c srcs/ft_printdigit.c srcs/ft_printhex.c srcs/ft_printpointer.c srcs/ft_printstr.c srcs/ft_printunsigned.c srcs/ft_strlen.c

OBJS := ${SRCS:.c=.o}

INCLUDE := -I .

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(NAME): $(OBJS)
	ar rcs $@ $^

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
