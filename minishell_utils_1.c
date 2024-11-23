/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:08:34 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/22 21:55:16 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_is_exist(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_free_env(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

int	ft_cmnd_nb(t_list *data)
{
	t_list	*tmp;
	int		i;

	tmp = data;
	i = 0;
	if (data == NULL)
	{
		return (0);
	}
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_herdoc_nb(t_list *save)
{
	int		i;
	t_dir	*redir_cur;
	t_list	*cur;

	i = 0;
	cur = save;
	if (save == NULL)
		return (0);
	while (cur != NULL)
	{
		redir_cur = cur->redir;
		while (redir_cur != NULL)
		{
			if (redir_cur->type == HEREDOC)
			{
				i++;
			}
			redir_cur = redir_cur->next;
		}
		cur = cur->next;
	}
	return (i);
}

int	ft_strnb(char **str)
{
	int	j;

	j = 0;
	while (str[j] != NULL)
	{
		j++;
	}
	return (j);
}
