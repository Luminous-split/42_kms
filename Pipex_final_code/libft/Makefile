NAME := libft.a

CC := cc

CFLAGS := -Wall -Wextra -Werror

RM := rm -f

SRC_MDTY1 := ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_strlen.c ft_tolower.c ft_toupper.c ft_atoi.c ft_bzero.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strdup.c ft_calloc.c

SRC_MDTY2 := ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c  ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRC_BONUS := ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstadd_back_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstadd_back_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

SRC := $(SRC_MDTY1) $(SRC_MDTY2)

OBJS := $(SRC:.c=.o)

BONUS_OBJS := $(SRC_BONUS:.c=.o)

INCLUDE := -I .

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(NAME): $(OBJS)
	ar rcs $@ $^

all: $(NAME)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $^

.PHONY: all clean fclean re bonus
