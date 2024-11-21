/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:46:58 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/21 19:11:08 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    initialize_data_of_replale(t_data_of_replace *data,char *command,char *var,char *value)
{
    data->i = 0;
    data->j = 0;
    data->len_val = ft_strlen(value);
    data->len_var = ft_strlen(var);
    data->len_all = ft_strlen(command) - data->len_var - 1 + data->len_val;
    data->what = 1;
}
char *ft_replace(char *command,char *var,char *value,int k)
{
    t_data_of_replace   data;
    initialize_data_of_replale(&data,command,var,value);
    data.resu = malloc(data.len_all + 1);
    while(command[data.i])
    {
        if(command[data.i] == '$' && data.what)
        {
            k = 0;
            while(value && (k < data.len_val))
            {
                data.resu[data.j++] = value[k++];
            }
            data.i += data.len_var;
            data.what = 0;
        }
        else
            data.resu[data.j++] = command[data.i];
        data.i++;
    }
    data.resu[data.j] = '\0';
    return(data.resu);
}

char *get_env_value(char **env, char *var)
{
    int i = 0;
    int len = ft_strlen(var);
    
    while(env[i])
    {
        if(ft_strcmp_len(env[i],var,len) == 0 && env[i][len] == '=')
            return(env[i] + len + 1);
        i++;
    }
    return(NULL);
}

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
char *ft_last_word(char *str) 
{
    char *last_word;
    int cout = 0;
    int len = ft_strlen(str);
    while(is_space(str[len - 1]) == 1)
    {
        len--;
        cout++;
    }
    while (len > 0 && is_space(str[len - 1]) == 0)
    {
        len--;
    }
    last_word = ft_substr(str,len,(ft_strlen(str) - cout) - len);
    return last_word;
}

void    free_for_can_replace(char **tmp,char **tmp1,char **sub)
{
    free((*sub));
    free((*tmp));
    free((*tmp1));
}
int can_replace(char **command ,int i,int j)
{
    char *tmp;
    char *tmp1;
    char *sub;

    sub = ft_substr(command[i],0,j);
    tmp = ft_last_word(sub);
    if(i > 0)
        tmp1 = ft_last_word(command[i - 1]);
    else
        tmp1 = ft_last_word(command[0]);
    if(command[i][j] == '$' && j == 1 && is_quote(command[i][0]) == 1 && ft_strcmp(tmp1,"<<") == 0)
    {
        free_for_can_replace(&tmp,&tmp1,&sub);
        return(1);
    }
    else if(command[i][j] == '$' && (j > 1 && ft_strcmp(tmp,"<<") == 0))
    {
        free_for_can_replace(&tmp,&tmp1,&sub);
        return(1);
    }
    free_for_can_replace(&tmp,&tmp1,&sub);
    return(0);
}
void    encryption(char *str)
{
    int i = 0;

    while(str[i])
    {
        if(str[i] == '<')
            str[i] ='\1';
        else if(str[i] == '>')
            str[i] ='\2';
        else if(str[i] == '|')
            str[i] ='\3';
        i++;
    }
}
void    hendled_expand(t_data_for_expand *data ,char **env,char ***command)
{
    if((*command)[data->i][data->j + 1] == '?')
    {
        data->value = get_env_value(env, "?");
        data->tmp = ft_replace((*command)[data->i], "?", data->value, 0);
        data->in = 1;
    }
    else if(((*command)[data->i][data->j + 1] == '@' || ft_isdigit((*command)[data->i][data->j + 1]) == 1))
    {
        data->var = ft_substr((*command)[data->i],data->j + 1,1);
        data->j += 1;
        data->tmp = ft_replace((*command)[data->i], data->var, "", 0);
        free (data->var);
        data->in = 1;
    }
    else if((*command)[data->i][data->j + 1] != ' ')
    {
        data->var = get_variable((*command)[data->i], data->j + 1);
        data->j += ft_strlen (data->var);
        data->value = get_env_value(env, data->var);
        if(data->value != NULL)
            encryption(data->value); 
        data->tmp = ft_replace((*command)[data->i], data->var, data->value, 0);
        free (data->var);
        data->in = 1;
    }
}
void    expand_command(t_data_for_expand *data,char ****command)
{
    data->in = 0;
    free((**command)[data->i]);
    (**command)[data->i] = data->tmp;
    data->len = ft_strlen((**command)[data->i]);
}
void    initialize_data_of_search_variable(t_data_for_expand   *data)
{
    data->i = -1;
    data->in = 0;
}
void  ft_search_variable(char ***command,char **env)
{
    t_data_for_expand data;
   initialize_data_of_search_variable(&data);
    
    while((*command)[++data.i])
    {
        data.len = ft_strlen((*command)[data.i]);
        if((*command)[data.i][0] != '\'')
        {
            data.j = -1;
            while (++data.j < data.len)
            {
                if((*command)[data.i][data.j] == '$')
                {
                    if(can_replace((*command),data.i,data.j) == 0)
                    {
                        hendled_expand(&data,env,command);
                        if(data.in == 1)
                        expand_command(&data,&command);
                    }
                }
            }
        }
    }
}
