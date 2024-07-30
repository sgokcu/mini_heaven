NAME	=	minishell

SRCS	=	main.c environment.c parsing/divide_prs.c parsing/struct_filling.c builtins/env.c

OBJS = $(SRCS:.c=.o)


CC	=	gcc
RM	=	rm -rf
CFLAGS	= -Wall -Wextra -Werror -g
LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(LIBFT) $(SRCS) -lreadline -o $(NAME)

clean:
		$(RM) $(OBJS) 

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re