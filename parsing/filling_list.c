/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:33:17 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/18 17:27:58 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
        else if (ft_strcmp (com[i], ">") == 0)
            filling_redir(list,OUT,com[++i], &c);
        else if (ft_strcmp (com[i], "<") == 0)
            filling_redir(list,IN,com[++i], &c);
        else
        {
            if(com[i][0] == '\"')
            {
                resu[j++] = disable(com[i]);
            }
            else
                resu[j++] = ft_strdup_and_remove_not_printible(com[i]);
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