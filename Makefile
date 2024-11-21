NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I.# -g -fsanitize=address

LDFLAGS = -lreadline

RM = rm -rf 

SRC = parsing/error.c parsing/expand.c parsing/free.c parsing/filling_list.c parsing/filling_command.c parsing/filling_redirections.c parsing/help_join.c parsing/help.c parsing/join.c parsing/main.c parsing/split_cmd_by_quote.c parsing/split_cmd_by_space.c minishell_utils.c execution.c herdoc.c builtine_command.c redirections.c 

 
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) minishell.h
	make -C libft 
	make -C ft_printf
	$(CC)  $(OBJ) libft/libft.a  ft_printf/libftprintf.a $(LDFLAGS) -o $(NAME)

clean:
	make -C libft clean
	make -C ft_printf clean
	$(RM) $(OBJ)

fclean: clean
	make -C libft fclean
	make -C ft_printf fclean
	$(RM) $(NAME) 

re: fclean all