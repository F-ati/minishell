/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_by_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:31:59 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/19 15:42:17 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
