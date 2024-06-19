NAME = minishell

CC = cc

SRC = src/main.c src/tokens.c src/input_check.c src/parser.c src/expanse.c src/expanse_utils.c src/utils.c\
	src/redir.c src/redir_utils.c src/heredoc.c src/exec.c src/main_copy.c src/env.c src/cd.c src/echo.c\
		src/exit.c src/input.c src/pwd.c src/unset.c src/export.c src/export_utils.c\
		src/cd_help.c src/s_split.c src/freedom.c src/token_utils.c src/signals.c\

CFLAGS = -Wall -Werror -Wextra -g

LINKS = -lreadline

OBJ = $(SRC:.c=.o)

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	cd libft && make
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LINKS)

clean:
	cd libft && make clean
	rm -rf $(OBJ)

fclean: clean
	cd libft && make fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re