/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:46:58 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/19 22:41:59 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
int can_replace(char **command ,int i,int j)
{
    
    if(command[i][j] == '$' && j == 1 && is_quote(command[i][0]) == 1 && ft_strcmp(ft_last_word(command[i - 1]),"<<") == 0)
    {
        return(1);
    }
    else if(command[i][j] == '$' && (j > 1 && ft_strcmp(ft_last_word(ft_substr(command[i],0,j)),"<<") == 0))
        return(1);
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
void  ft_search_variable(char ***command,char **env)
{
    int i = -1;
    int j = 0;
    char *var;
    char *value;
    char *tmp;
    int len;
    int in = 0;
    
    while((*command)[++i])
    {
        len = ft_strlen((*command)[i]);
        if((*command)[i][0] != '\'')
        {
            j = -1;
            while (++j < len)
            {
                if((*command)[i][j] == '$')
                {
                    if(can_replace((*command),i,j) == 0)
                    {
                        if((*command)[i][j + 1] == '?')
                        {
                            value = get_env_value(env, "?");
                            tmp = ft_replace((*command)[i], "?", value, 0);
                            in = 1;
                        }
                        else if(((*command)[i][j + 1] == '@' || ft_isdigit((*command)[i][j + 1]) == 1))
                        {
                            var = ft_substr((*command)[i],j + 1,1);
                            j += 1;
                            tmp = ft_replace((*command)[i], var, "", 0);
                            free (var);
                            in = 1;
                        }
                        else if((*command)[i][j + 1] != ' ')
                        {
                            var = get_variable((*command)[i], j + 1);
                            j += ft_strlen (var);
                            value = get_env_value(env, var);
                            // printf("====%s\n",value);
                            if(value != NULL)
                                encryption(value); 
                            // printf("====%s\n",value);
                            tmp = ft_replace((*command)[i], var, value, 0);
                            free (var);
                            in = 1;
                           // free (value);
                        }
                        if(in == 1)
                        {
                            in = 0;
                            free((*command)[i]);
                            (*command)[i] = tmp;
                            // printf("*****%s\n",tmp);
                            len = ft_strlen((*command)[i]);
                        }
                    }
                }
            }
        }
    }
}
