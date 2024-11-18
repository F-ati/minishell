/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:46:58 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/18 13:13:04 by fel-aziz         ###   ########.fr       */
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
                if((*command)[i][j] == '$' && (*command)[i][j + 1] == '?')
                {
                    value = get_env_value(env, "?");
                    tmp = ft_replace((*command)[i], "?", value, 0);
                    free((*command)[i]);
                    (*command)[i] = tmp;
                    len = ft_strlen((*command)[i]);
                }
                else if((*command)[i][j] == '$' && (*command)[i][j + 1] != ' ')
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
