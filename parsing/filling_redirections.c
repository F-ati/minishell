/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:40:38 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/16 20:42:40 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    t_dir *dir;
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