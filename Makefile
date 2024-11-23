NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I. $(READLINE_FLAGS)

READLINE_FLAGS =  #-I/Users/$(USER)/.brew/opt/readline/include
READLINE_LIB = #-L/Users/$(USER)/.brew/opt/readline/lib

LDFLAGS = -lreadline

# SRC = parsing/error.c parsing/expand.c parsing/free.c parsing/filling_list.c parsing/filling_command.c parsing/filling_redirections.c parsing/help_join.c parsing/help.c parsing/join.c parsing/split_cmd_by_quote.c parsing/split_cmd_by_space.c minishell_utils_1.c execution.c herdoc.c builtine_command_1.c redirections.c parsing/main.c builtine_command_2.c builtine_utils.c
SRC = parsing/error.c parsing/expand.c parsing/expand_utils.c parsing/free.c parsing/filling_list.c parsing/filling_command.c parsing/filling_redirections.c parsing/help_join.c parsing/help.c parsing/join.c parsing/split_cmd_by_quote.c parsing/split_cmd_by_space.c minishell_utils_1.c execution.c herdoc.c builtine_command_1.c redirections.c parsing/main.c builtine_command_2.c builtine_utils.c minishell_utils_2.c minishell_utils_3.c minishell_utils_4.c minishell_utils_5.c minishell_utils_6.c minishell_utils_7.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

# parsing/main.o: parsing/main.c
# 	$(CC) $(CFLAGS) $(READLINE_FLAGS) -c $< -o $@

$(NAME): $(OBJ) minishell.h
	make -C libft
	make -C ft_printf
	$(CC) $(OBJ) libft/libft.a ft_printf/libftprintf.a $(READLINE_LIB) $(LDFLAGS) -o $(NAME)

clean:
	make -C libft clean
	make -C ft_printf clean
	$(RM) $(OBJ)

fclean: clean
	make -C libft fclean
	make -C ft_printf fclean
	$(RM) parsing/main.o
	$(RM) $(NAME)

re: fclean all

