/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:12:00 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/23 21:15:02 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_node(t_list *list)
{
	t_dir	*red;

	free_arr(list->command);
	list->command = NULL;
	while (list->redir)
	{
		red = list->redir;
		list->redir = list->redir->next;
		free(red->file_name);
		if (red->type == HEREDOC)
			free(red->herdoc_file_name);
		red->type = 0;
		red->file_name = NULL;
		red->herdoc_file_name = NULL;
		free(red);
		red = NULL;
	}
	list->next = NULL;
}

void	free_list(t_list *list)
{
	t_list	*lst;

	while (list)
	{
		lst = list;
		list = list->next;
		free_node(lst);
		free(lst);
		lst = NULL;
	}
}

void	free_for_can_replace(char **tmp, char **tmp1, char **sub)
{
	free((*sub));
	free((*tmp));
	free((*tmp1));
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
