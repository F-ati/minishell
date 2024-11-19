/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:30:10 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/19 22:41:07 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redirection(char *str)
{
    if(ft_strcmp(str,"<<") == 0 || ft_strcmp(str,"<") == 0 || ft_strcmp(str,">>") == 0
    || ft_strcmp(str,">") == 0)
        return(1);
    return(0);
}
int ft_arry_len(char **str)
{
    int i;
    i = 0;

    while(str[i])
    {
        i++;
    }
    return(i);
}
int    check_error(char **command)
{
    int len;
    int i;

    i = 0;
    len = ft_arry_len(command);
    if(ft_strcmp(command[0],"|") == 0 || ft_strcmp(command[len - 1],"<") == 0 || ft_strcmp(command[len - 1 ],">") == 0 
    || ft_strcmp(command[len - 1 ],"<<") == 0 || ft_strcmp(command[len - 1 ],">>") == 0 || ft_strcmp(command[len - 1],"|") == 0)
        return(1);
    while(command[i + 1])
    {
        if(is_redirection(command[i]) == 1 && ( is_redirection(command[i + 1]) == 1 || ft_strcmp(command[i + 1],"|") == 0))
            return(1);
        i++;
    }
    return(0);
}