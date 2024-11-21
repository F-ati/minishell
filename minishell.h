#ifndef MINISHELL_H
#define MINISHELL_H

#define HEREDOC 1
#define APPEND 2
#define IN 3
#define OUT 4


#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include <readline/readline.h>
#include <readline/history.h>

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

typedef struct s_data
{
    int c;
    char **com;
    char **command;
    char *input;
}   t_data;

typedef struct s_data_for_split_quote
{
    int count;
    int in_quote;
    int start;
    char quote_char;
    int i;
}   t_data_for_split_quote;
typedef struct s_data_for_add_command
{
    char **resu;
    int i;
    int j;
    int c;
}   t_data_for_add_command;

typedef struct s_data_of_replace
{
    int i;
    int j;
    int len_val;
    int len_var;
    int len_all;
    char *resu;
    int what;
}   t_data_of_replace;

typedef struct s_data_for_expand
{
    int i;
    int j;
    char *var;
    char *value;
    char *tmp;
    int len;
    int in;
}   t_data_for_expand;

typedef struct s_shell
{
    char **env;
    char **export;
    t_list *list;
    t_data data;
    int exit_status;
    // my vriable (execution);
    int len ;
    char **path;
    int i ;
    int herdoc_nb;
    int cmd_nb;
}   t_shell;
//======================================PARSING================================================
void printer(char **a);
// error //
int is_redirection(char *str);
int ft_arry_len(char **str);
int    check_error(char **command);

// help //
int ft_strcmp_len(char *s1,char *s2, int len);
int is_quote(char c);
int ft_close(char *str, char c,int n, int start);
char    *ft_substr_add_space(char *s, int start, int len);
void fix_quotes (char **str);

// split_command//
char **ft_split_command(char *str,int *n);
int ft_check(char *str);
void ft_split_quote(char *str, char ***command);

// expand //
char *ft_replace(char *command,char *var,char *value,int k);
char *get_env_value(char **env, char *var);
char *get_variable(char *command,int pos);
void  ft_search_variable(char ***command,char **env);

// help join //
void    ft_strcpy(char *s1, char *s2);
int is_space_or_quote(char c);
char *ft_remove(char *str,int len_r, int n);
char *get_last_word(char *str);
char *get_first_word(char *str); 

// join //
void    ft_collect_in_first(char **next,char **str);
void    ft_collect_in_last(char **next,char **str);
char **ft_join(char **str);
void    ft_join_quote(char **str);

// split_by_space //

int is_space(char c);
int	check_command(const char *str);
char	**ft_split_by_space_tab(char const *s);
char **ft_split_by_space(char **str);

// filling //
int    filling(char **resu,char *str,char **arry,int i);
void    ft_filling(char *s,char **s1,int lenf,int start);
char **ft_add_command(char **com,int start,int pos,t_list *list);
t_list    *creat_list(char **com,int start,int pos,int *c);
void   add_node(t_list *list,char **com,int start,int pos);
t_list    *ft_filling_list(char **com);
char *disable(char *str);
t_dir    *creat_dir_list(int typ,char *name);
void    add_dir_node(t_dir  *redir,int typ,char *name);
void    filling_redir(t_list *list,int typ,char *name,int *c);


// free //
void	free_arr(char **str);
void    free_node(t_list *list);
void    free_list(t_list *list);
//==============================================EXECUTION======================================================
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
int   check_invalid_arg(char *command);
int   ft_check_is_exist(char *str,char c);
int  ft_open_output(char *file_name ,t_shell  *shell);
int  ft_open_append(char *file_name ,t_shell *shell);
int  ft_open_input(char *file_name ,t_shell *shell);
void  execute_simple_command(t_shell *shell , int flag);
void  handle_heredoc(t_shell *shell);
char *get_variable(char *command,int pos);
int	ft_write_data(int fd, char *value);
// int   nb_of_command(t_list *list);
int ft_open_redictions(t_shell *shell);
char	*my_strjoin(char  *s1, char  *s2);
void  ft_search_variable(char ***command,char **env);
char *ft_replace(char *command,char *var,char *value,int k);
void ft_apdate_env(t_shell *shell,char *new_arg);
void update_exit_status_env(t_shell *shell);
int	display_variable(t_shell *shell, char *str, int i, int fd);
char	*generate_temp_filename(char *file_name);
int	ft_handle_input_redirection(t_shell *shell, t_dir *redir);
int	ft_handle_output_redirection(t_shell *shell, t_dir *redir);
void print_error(t_shell  *shell,char *old_pwd);
char *go_to_home(t_shell *shell);
// int ft_pipe(t_shell *shell);
// int   is_parent_command( t_shell *shell);


// void ft_herdoc(t_shell *data);
#endif