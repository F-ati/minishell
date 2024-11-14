#ifndef MINISHELL_H
#define MINISHELL_H

#define BUFFER_SIZE 1024
#define HEREDOC 1
#define APPEND 2
#define IN 3
#define OUT 4
#define PATH_MAX 4096 


#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include "libft/libft.h"
// remove strncmp;

typedef struct s_dir
{
    int type;
    char    *file_name;
    char    *herdoc_file_name;
    int is_quoted;
    struct s_dir    *next;
}   t_dir;

typedef struct s_list
{
    char    **command;
    t_dir   *redir;
    int     fd_input;
    int     fd_output;
    int     fd_heredoc;
    struct s_list   *next;
}   t_list;

typedef struct s_shell
{
    char **env;
    char **export;
    t_list *list;
    int exit_status;
    // my vriable (execution);
    int len ;
    char **path;
    int i ;
    int herdoc_nb;
    int cmd_nb;
}   t_shell;

// funcs of the execution  
void  ft_execution(t_shell *minishell);
int   ft_cmnd_nb( t_list *data);
void  ft_echo(t_shell *shell);
void  ft_env(t_shell *data);
void  ft_cd(t_shell *shell);
void  ft_pwd(t_shell *shell);
void  ft_unset(t_shell *data);
void  ft_export(t_shell *shell);
int   ft_herdoc_nb(t_list *save);
void  ft_exit(t_shell *shell);
int   ft_strnb(char **str);
int   ft_herdoc( t_shell *shell,t_dir *redir);
int   get_var_indix(char **exp_or_env,char *name_var);
int	  ft_check_is_number(char *str);
int   cmmnd_len(char **str);
char  *get_env_value(char **env, char *var);
int   ft_strcmp_len(char *s1,char *s2, int len);
int   check_invalid_arg(char *command);
int   ft_check_is_exist(char *str,char c);
int  ft_open_output(char *file_name ,t_shell  *shell);
int  ft_open_append(char *file_name ,t_shell *shell);
int  ft_open_input(char *file_name ,t_shell *shell);
void  execute_simple_command(t_shell *shell , int flag);
void  handle_heredoc(t_shell *shell);
// int   nb_of_command(t_list *list);
int ft_open_redictions(t_shell *shell);
char	*my_strjoin(char  *s1, char  *s2);
void	free_arr(char **str);
// int ft_pipe(t_shell *shell);
// int   is_parent_command( t_shell *shell);


// void ft_herdoc(t_shell *data);

#endif