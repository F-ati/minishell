NAME = minishell

CC = cc

 CFLAGS = -Wall -Wextra -Werror -I.

LDFLAGS = -lreadline

RM = rm -rf 

SRC = parsing/error.c parsing/expand.c parsing/free.c parsing/filling_list.c parsing/filling_command.c parsing/filling_redirections.c parsing/help_join.c parsing/help.c parsing/join.c parsing/main.c parsing/split_cmd_by_quote.c parsing/split_cmd_by_space.c 
 
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) minishell.h
	make -C libft
	$(CC)  $(OBJ) libft/libft.a $(LDFLAGS) -o $(NAME)

clean:
	make -C libft clean
	$(RM) $(OBJ) 

fclean: clean
	make -C libft fclean
	$(RM) $(NAME) 

re: fclean all