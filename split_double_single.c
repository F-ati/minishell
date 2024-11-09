/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_double_single.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 10:01:06 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/09 18:15:32 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int is_space(char c) 
{
    return (c == ' ' || c == '\t');
}

int	check_command(const char *str)
{
	int	i;
	int	word;
	int	what;

	i = 0;
	word = 0;
	what = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (is_space(str[i]) == 0 && what == 0)
		{
			word++;
			what = 1;
		}
		else if (is_space(str[i]) == 1)
			what = 0;
		i++;
	}
	return (word);
}

 void	*free_arry(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (NULL);
}

char	**ft_split_by_space_tab(char const *s)
{
	char	**result;
	int		i;
	int		j;
	int		start;

	i = 0;
	start = 0;
	j = 0;
	result = malloc(sizeof(char *) * (check_command(s) + 1));
	if (result == NULL)
		return (NULL);
	while (j < check_command(s))
	{
		while (s[i] && is_space(s[i]) == 1)
			i++;
		start = i;
		while (s[i] && is_space(s[i]) == 0)
			i++;
		result[j] = ft_substr(s, start, i - start);
		if (result[j] == NULL)
			return (free_arry(result, j));
		j++;
	}
	result[j] = NULL;
	return (result);
}
int ft_close(char *str, char c,int n, int start) 
{    
    int i ;
    i = start + 1;
    if(n == 1)
    {
    while (str[i] && str[i] != c)
        i++;
    if (str[i] == c)
        return (i + 1);
    }
    else if(n == 0)
    {
    while (str[i] && str[i] != c)
        i++;
    if (str[i] == c )
        return (i);
    else if(str[i] == '\0')
        return(i);
    }
    return (-1);
}

int ft_check(char *str)
{
    int i;
    int k;
    int xhal;
    
    i = 0;
    k = 0;
    xhal = 0;
    while(str[i] != '\'' && str[i] != '\"' && str[i])
        i++;
    if(str[i] == '\0')
        return(0);
    else
    {
        if(i != 0)      
          xhal++;
        while(str[i])
        {
            if(str[i] == '\'')
                k = ft_close(str,'\'',1,i);
            else if(str[i] == '\"')
                k = ft_close(str,'\"',1,i);
            else if(str[i] != '\'' && str[i] != '\"')
            {
              if(ft_close(str,'\'',0,i) <= ft_close(str,'\"',0,i))
                  k = ft_close(str,'\'',0,i);
              else
                  k = ft_close(str,'\"',0,i);
            }
            if(k != -1)
                xhal++;
            else
                return(-1);
            i = k ;
        }
    }
    return(xhal);
}

int is_quote(char c) 
{
    if (c == '\'' || c == '\"') 
        return (1);
   return 0;
}
void    ft_filling(char *s,char **s1,int lenf,int start)
{
    int i;
    
    i = 0;
    while (i < lenf)
    {
        if(s[start] == '|' || s[start] == '<'  || s[start] == '>')
        {
            (*s1)[i++] = ' ';
            (*s1)[i++] = s[start++];
            if((s[start] == '<' || s[start] == '>') && s[start - 1] == s[start])
                (*s1)[i++] = s[start++];
            (*s1)[i] = ' ';
        }
        else
            (*s1)[i] = s[start++];
        i++;
    }
    (*s1)[i] = '\0';
}
char    *ft_substr_add_space(char *s, int start, int len)
{
    char    *s1;
    int i;
    int lenf;
    int size;

    size = 1;
    i = -1;
    if (start > ft_strlen(s))
        return (ft_calloc(1, 1));
    if ((start + len) > ft_strlen(s))
        len = ft_strlen(s) - start;
    lenf = len;
    while (++i < len)
    {
        if(s[start + i] == '|' || size == 2 ||  (s[start + i] == '<' && s[start + i + 1] != '<') || (s[start + i] == '>' && s[start + i + 1] != '>'))
        {
            lenf += 2;
            size = 1;
        }
        else if((s[start + i] == '<' && s[start + i + 1] == '<') || (s[start + i] == '>' && s[start + i + 1] == '>'))
            size+= 1;
    }
    s1 = malloc((lenf + 1) * sizeof(char));
    ft_filling(s,&s1,lenf,start);
    return (s1);
}

void ft_split_quote(char *str, char ***command) 
{
    int count = 0;
    int in_quote = 0;
    int start = 0;
    char quote_char = '\0';
    int i = 0;

    while (str[i] != '\0') 
    {
        if (is_quote(str[i])) 
        {
            if (in_quote == 1 && str[i] == quote_char) 
            {
                in_quote = 0;
                (*command)[count++] = ft_substr(str ,start , i - start + 1);
                start = i + 1;
            } 
            else if (in_quote == 0) 
            {
                if (i > start) 
                    (*command)[count++] = ft_substr_add_space(str ,start, i - start);
                in_quote = 1;
                quote_char = str[i];
                start = i;
            }
        }
        i++;
    }
    if (i > start)
        (*command)[count++] = ft_substr_add_space(str , start, i - start);
    (*command)[count] = NULL;
}

char **ft_split_command(char *str,int *n)
{
    char **command;
    int len;

    if(str[0] == '\0')
        return(NULL);
    len = ft_check(str);
    if (len == -1)
    {
        ft_putstr_fd("Error: Unmatched quotes\n",2);
        (*n) = 2;
        return NULL;
    }
    else if (len == 0)
    {
        command = malloc(sizeof(char *) * 2);
        command[0] = ft_substr_add_space(str , 0, ft_strlen(str));
        command[1] = NULL;
    }
    else
    {
        command = malloc(sizeof(char *) * (len + 1));
        ft_split_quote(str,&command);
    }
    return command;
}

void printer(char **a)
{
    int i;

    i = 0;
    while (a[i])
        printf ("--%s--\n", a[i++]);    
}
// int ft_strcmp_len(char *s1,char *s2, int len)
// {
//     int	i;

// 	i = 0;
// 	while (i < len && s1[i] && s2[i])
// 	{
//         if(s1[i] == s2[i])
//             i++;
//         else
//             break;
// 	}
//     if(i == len)
//         return(0);
//     return (s1[i] - s2[i]);
// }

// char *get_env_value(char **env, char *var)
// {
//     int i = 0;
//     int len = ft_strlen(var);
    
//     while(env[i])
//     {
//         if(ft_strcmp_len(env[i],var,len) == 0 && env[i][len] == '=')
//             return(env[i] + len + 1);
//         i++;
//     }
//     return(NULL);
// }
char *get_variable(char *command,int pos)
{
    char *var;
    int i = 0;
    while(command[i + pos])
    {
        if(ft_isalnum(command[i + pos])== 0)
            break;
        i++;
    }
    var = ft_substr(command,pos,i);
    return(var);
}
char *ft_replace(char *command,char *var,char *value,int k)
{
    int i = 0;
    int j = 0;
    int len_val = ft_strlen(value);
    int len_var = ft_strlen(var);
    int len_all = ft_strlen(command) - len_var - 1 + len_val;
    char *resu;
    int lock = 1;

    resu = malloc(len_all + 1);
    while(command[i])
    {
        if(command[i] == '$' && lock)
        {
            k = 0;
            while(value && (k < len_val))
            {
                resu[j++] = value[k++];
            }
            i += len_var;
            lock = 0;
        }
        else
            resu[j++] = command[i];
        i++;
    }
    resu[j] = '\0';
    return(resu);
}
void  ft_search_variable(char ***command,char **env)
{
    int i = -1;
    int j = 0;
    char *var;
    char *value;
    char *tmp;
    int len;
    
    while((*command)[++i])
    {
        len = ft_strlen((*command)[i]);
        if((*command)[i][0] != '\'')
        {
            j = -1;
            while (++j < len)
            {
                if((*command)[i][j] == '$' && ((*command)[i][j + 1] != '?' && (*command)[i][j + 1] != ' '))
                {
                    var = get_variable((*command)[i], j + 1);
                    j += ft_strlen (var);
                    value = get_env_value(env, var);
                    tmp = ft_replace((*command)[i], var, value, 0);
                    free (var);
                    free((*command)[i]);
                    (*command)[i] = tmp;
                    len = ft_strlen((*command)[i]);
                }
            }
        }
    }
}

int is_space_or_quote(char c) 
{
    return (c == ' ' || c == '\t' || c == '\'' || c == '\"');
}

char *get_last_word(char *str) 
{
    char *last_word;
    int len = ft_strlen(str);
    while (len > 0 && !is_space(str[len - 1])) {
        len--;
    }
    last_word = ft_strdup(&str[len]);
    return last_word;
}

char *get_first_word(char *str) {
    int len = 0;
    int i = 0;
    while (str[len] && !is_space(str[len])) {
        len++;
    }
    char *word = (char *)malloc(len + 1);
    while(i < len)
    {
        word[i] = str[i];
        i++;
    }
     word[i] = '\0';
    return word;
}
void    ft_strcpy(char *s1, char *s2)
{
	int i = 0;
	
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}
char *ft_remove(char *str,int len_r, int n)
{
    int i;
    int j;
    int len;
    int len_s;
    char *resu;

    len_s = ft_strlen(str);
    len = len_s - len_r + 1;
    resu = malloc(len);
    i  = 0;
    if(n == 1)
    {
        i = -1;
        while(++i < len - 1)
            resu[i] = str[i];
    }
    else if(n == 0)
    {
        i = len_r;
        j = 0;
        while(j < len - 1)
            resu[j++] = str[i++];
        i = j;
    }
    resu[i] = '\0';
    return(resu);
}
void    ft_collect_in_first(char **next,char **str)
{
    int len_next;
    int len_word;
    char *word;
    char *new_next;
    char *new_str;
    word = get_last_word((*str));
    len_word = ft_strlen(word);
    len_next = ft_strlen((*next));
    new_next = malloc(len_next + len_word + 1);
    new_next[0] = (*next)[0];
    ft_strcpy(new_next + 1, word);

    ft_strcpy(new_next + (1 + len_word), (*next) + 1);
    free((*next));
    (*next) = new_next;
    free(word);
    new_str = ft_remove((*str),len_word, 1);
    free((*str));
    (*str) = new_str;
}
void    ft_collect_in_last(char **next,char **str)
{
    int len_next;
    int len_word;
    char *word;
    char *new_next;
    char *new_str;
    word = get_first_word((*str));
    len_word = ft_strlen(word);
    len_next = ft_strlen((*next));
    new_next = malloc(len_next + len_word + 1);
    ft_strcpy(new_next ,(*next));
    ft_strcpy(new_next + (len_next - 1), word);
    new_next[len_next + len_word - 1] = (*next)[len_next - 1];
    new_next[len_next + len_word ] = '\0';
    free((*next));
    (*next) = new_next;
    free(word);
    new_str = ft_remove((*str),len_word, 0);
    free((*str));
    (*str) = new_str;
}
void ft_fix(char *str)
{
    int i = ft_strlen (str);
    if (str[0] == '\'')
    {
        str[0] = '\"';
        while (i >= 0)
        {
            if (str[i] == '\'')
            {
                str[i] = '\"';
                break ;
            }
            i--;
        }
    }
}
char **ft_join(char **str)
{
    int i = 0;
    int len;
    int k = 0;

    while (str[i] && str[i + 1]) 
    {
        len = ft_strlen(str[i]);
       if(is_space_or_quote(str[i][len - 1]) == 0 && (str[i + 1][0] == '\'' || str[i + 1][0] == '\"'))
       {
            ft_collect_in_first(&str[i + 1],&str[i]); 
            if(ft_strcmp(str[i],"\0") == 0)
            {
                k = i;
                free(str[k]);
                while(str[k + 1])
                {
                    str[k] = str[k + 1];
                    k++;
                }
                str[k] = NULL;
            }
       }
       else if((str[i][len - 1] == '\'' || str[i][len - 1] == '\"') && is_space_or_quote(str[i + 1][0]) == 0)
       {
            ft_collect_in_last(&str[i],&str[i + 1]);
            if(ft_strcmp(str[i + 1],"\0") == 0)
            {
                k = i + 1;
                free(str[k]);
                while(str[k + 1])
                {
                    str[k] = str[k + 1];
                    k++;
                }
                str[k] = NULL;
            }
       }
        i++;
    }
    return str;
}

void    ft_join_quote(char **str)
{
    int i = 0;
    int len_str;
    int len_next;
    char *new_str;
    int k = 0;
    
    while(str[i] && str[i + 1])
    {
            len_str = strlen(str[i]);
            len_next = strlen(str[i + 1]);
        if((str[i][len_str - 1] == '\'' || str[i][len_str - 1] == '\"') && (str[i + 1][0] == '\'' || str[i + 1][0] == '\"'))
        {
            new_str = malloc(len_str + len_next - 1);
            ft_strcpy(new_str,str[i]);
            ft_strcpy(new_str + len_str - 1,str[i + 1] + 1);
            free(str[i]);
            str[i] = new_str;
            k = i + 1;
            free(str[k]);
            while(str[k + 1])
            {
                str[k] = str[k + 1];
                k++;
            }
            str[k] = NULL;
            i = -1;
        }
        i++;
    }
}

void fix_quotes (char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        ft_fix(str[i]);
        i++;
    }
}
int ft_len_arry(char **str)
{
    int i;
    i = 0;

    while(str[i])
    {
        i++;
    }
    return(i);
}
int    filling(char **resu,char *str,char **arry,int i)
{
    int j;
    j = 0;
    
    if(str != NULL)
    {
        resu[i] = ft_strdup(str);
        i++;
    }
    else
    {
        while(arry[j])
        {
            resu[i] = ft_strdup(arry[j]);
            j++;
            i++;
        }
    }
    resu[i] = NULL;
    return(i);
}
char **ft_split_by_space(char **str)
{
    char **mini_str;
    char **resu;
    int i = 0;
    int count = 0;
    int j = 0;
    
    while (str[i])
    {
        if (str[i][0] != '"' && str[i][0] != '\'')
            count += check_command(str[i]);
        else
            count++;
        i++;
    }
    resu = malloc(sizeof(char *) * (count + 1));
    i = 0;
    while (str[i])
    {
        if (str[i][0] != '"' && str[i][0] != '\'')
        {
            mini_str = ft_split_by_space_tab(str[i]);
            j = filling(resu, NULL, mini_str, j);
            // free_arr(mini_str);
        }
        else
            j = filling(resu, str[i], NULL, j);
        i++;
    }
    return (resu);
}

char *disable(char *str)
{
    int  i = 1;
    int j = 0;
    int len  = ft_strlen(str);
    char *resu;

    resu = malloc(len -1);
    while(i < len - 1)
        resu[j++] = str[i++];
    resu[j] = '\0';
    return(resu);
}

t_dir    *creat_dir_list(int typ,char *name)
{
    t_dir  *redir;
    
    redir = malloc(sizeof(t_dir));
    redir->type = typ;
    redir->is_quoted = 0;
    if(name[0] == '\"')
    {
        redir->file_name = disable(name);
        if(typ == HEREDOC)
            redir->is_quoted = 1;
    }
    else
        redir->file_name =  ft_strdup(name);
    redir->next = NULL;
    return(redir);
}
void    add_dir_node(t_dir  *redir,int typ,char *name)
{
    t_dir *dir = NULL;
    dir = creat_dir_list(typ,name);
    while(redir->next)
        redir = redir->next;
    redir->next = dir;
}
void    filling_redir(t_list *list,int typ,char *name,int *c)
{
    if((*c) == 0)
    {
        list->redir = creat_dir_list(typ,name);
        (*c) = 1;
    }
    else
        add_dir_node(list->redir,typ,name);
}


char **ft_add_command(char **com,int start,int pos,t_list *list)
{
    char **resu;
    int i = start;
    int j = 0;
    int c = 0;

    resu = ft_calloc(sizeof(char *), (pos + 1));
    while(i < pos)
    {
        if (ft_strcmp (com[i], "<<") == 0)
            filling_redir(list,HEREDOC,com[++i], &c);
        else if (ft_strcmp (com[i], ">>") == 0)
            filling_redir(list,APPEND,com[++i], &c);
        else if (ft_strcmp (com[i], "<") == 0)
            filling_redir(list,IN,com[++i], &c);
        else if (ft_strcmp (com[i], ">") == 0)
            filling_redir(list,OUT,com[++i], &c);
        else
        {
            if(com[i][0] == '\"')
            {
                resu[j++] = disable(com[i]);
            }
            else
                resu[j++] = ft_strdup(com[i]);
        }
        i++;
    }
    return (resu);
}


t_list    *creat_list(char **com,int start,int pos)
{
    t_list  *list;
    
    list = malloc(sizeof(t_list));
    list->redir = NULL;
    list->command = ft_add_command(com ,start,pos,list);
    list->next = NULL;
    
    return(list);
}
void   add_node(t_list *list,char **com,int start,int pos)
{
    t_list *lst;
    lst = creat_list(com ,start,pos);
    while(list->next)
        list = list->next;
    list->next = lst;
}
void print_list(t_list *list)
{
    while (list)
    {
        printer (list->command);
        while (list->redir)
        {
            if (list->redir->type)
              printf ("redir type : %d and redir type : %s is_quated = %d\n", list->redir->type, list->redir->file_name,list->redir->is_quoted);
            list->redir = list->redir->next;
        }
        list = list->next;
    }
}
t_list    *ft_filling_list(char **com)
{
    int i = 0;
    t_list  *list;
    int c = 0;
    int start = 0;

    while(com[i])
    {
        if(ft_strcmp(com[i],"|") == 0  && c == 0)
        {
            list = creat_list(com ,start, i);
            c = 1;
            start = i + 1;
        }
        else if(ft_strcmp(com[i],"|") == 0  && c == 1)
        {
            add_node(list,com,start,i);
            start = i + 1;
        }
        i++;
    }
    if(c == 0)
    {
        list = creat_list(com ,start, i);
        c = 1;
    }
    else if(c == 1)
        add_node(list,com,start,i);
    return(list);
}

char **ft_strdup_arr(char **env)
{
    int len = ft_len_arry(env);
    int  i = 0;
    char **resu;

    resu = ft_calloc(sizeof(char *) , len + 1);
    while(i < len)
    {
        resu[i] = ft_strdup(env[i]);
        i++;
    }
    return(resu);
}

void init_shell(t_shell *minishell,char **env)
{
    minishell->env = ft_strdup_arr(env);
    minishell->export = ft_strdup_arr(env);
    minishell->exit_status = 0;
    minishell->list = NULL;
}
int is_redirection(char *str)
{
    if(ft_strcmp(str,"<<") == 0 || ft_strcmp(str,"<") == 0 || ft_strcmp(str,">>") == 0
    || ft_strcmp(str,">") == 0)
        return(1);
    return(0);
}
int    check_error(char **command)
{
    int len;
    int i;

    i = 0;
    len = ft_len_arry(command);
    if(ft_strcmp(command[0],"|") == 0 || ft_strcmp(command[len - 1],"<") == 0 || ft_strcmp(command[len - 1 ],">") == 0 
    || ft_strcmp(command[len - 1 ],"<<") == 0 || ft_strcmp(command[len - 1 ],">>") == 0)
        return(1);
    while(command[i + 1])
    {
        if(is_redirection(command[i]) == 1 && ( is_redirection(command[i + 1]) == 1 || ft_strcmp(command[i + 1],"|") == 0))
            return(1);
        i++;
    }
    return(0);
}
 void	free_arr(char **str)
{
    int i;

    i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
void    free_node(t_list *list)
{
    t_dir   *red;

    free_arr(list->command);
    list->command = NULL;
    while(list->redir)
    {
        red = list->redir;
        list->redir = list->redir->next;
        red->type = 0;
        free(red->file_name);
        red->file_name = NULL;
        free(red);
        red = NULL;
    }
    list->next = NULL;
}

void    free_list(t_list *list)
{
    t_list *lst;
    while(list)
    {
        lst = list;
        list = list->next;
        free_node(lst);
        free(lst);
        lst = NULL;
    }
}
// void    leak()
// {
//     system("leak minishell");
// }
int main(int ac,char **av,char **env)
{
    // atexit(leak);
    (void)ac;
    (void)av;
    int c = 0;
    char **com;
    char **command;
    char *input;
    t_shell minishell;
    init_shell (&minishell,env);
    minishell.exit_status = 0;
    while(1)
    {
        
        input = readline("minishell$ ");
        if(input == NULL)
        {
            // atexit(leak);
            break ;
        }
        com = ft_split_command(input,&minishell.exit_status);
        if (com)
        {
            ft_search_variable(&com,minishell.env);
            fix_quotes(com);
            ft_join(com);
            ft_join_quote(com);
            command = ft_split_by_space(com);
            // free_arr(com);
            c = check_error(command);
            if(c == 0)
            {
                minishell.list = ft_filling_list(command);
                // print_list (minishell.list);
                ft_execution (&minishell);
              //  free_list (minishell.list);
            }
            else
            {
                ft_putstr_fd("minishell: syntax error\n",2);
                minishell.exit_status = 2;
            }
            free_arr(command);
        }
        add_history(input);
        free (input);
    }
    free_arr(minishell.env);
    free_arr(minishell.export);
}
