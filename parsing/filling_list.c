/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:33:17 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/21 12:41:19 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	decrypt(char **command)
{
	int	i;
	int	j;

	i = 0;
	while (command[i])
	{
		j = 0;
		while (command[i][j])
		{
			if (command[i][j] == '\1')
				command[i][j] = '<';
			else if (command[i][j] == '\2')
				command[i][j] = '>';
			else if (command[i][j] == '\3')
				command[i][j] = '|';
			j++;
		}
		i++;
	}
}
void	initialize_for_add_command(t_data_for_add_command *data, int start)
{
	data->i = start - 1;
	data->j = 0;
	data->c = 0;
}
char	**ft_add_command(char **com, int start, int pos, t_list *list)
{
	t_data_for_add_command	data;

	initialize_for_add_command(&data, start);
	data.resu = ft_calloc(sizeof(char *), (pos + 1));
	while (++data.i < pos)
	{
		if (ft_strcmp(com[data.i], "<<") == 0)
			filling_redir(list, HEREDOC, com[++data.i], &data.c);
		else if (ft_strcmp(com[data.i], ">>") == 0)
			filling_redir(list, APPEND, com[++data.i], &data.c);
		else if (ft_strcmp(com[data.i], ">") == 0)
			filling_redir(list, OUT, com[++data.i], &data.c);
		else if (ft_strcmp(com[data.i], "<") == 0)
			filling_redir(list, IN, com[++data.i], &data.c);
		else
		{
			if (com[data.i][0] == '\"')
				data.resu[data.j++] = disable(com[data.i]);
			else
				data.resu[data.j++] = ft_strdup_and_remove_not_printible(com[data.i]);
		}
	}
	decrypt(data.resu);
	return (data.resu);
}
t_list	*creat_list(char **com, int start, int pos, int *c)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	list->redir = NULL;
	list->command = ft_add_command(com, start, pos, list);
	list->next = NULL;
	(*c) = 1;
	return (list);
}
void	add_node(t_list *list, char **com, int start, int pos)
{
	t_list	*lst;
	int		c;

	c = 0;
	lst = creat_list(com, start, pos, &c);
	while (list->next)
		list = list->next;
	list->next = lst;
}

t_list	*ft_filling_list(char **com)
{
	int		i;
	t_list	*list;
	int		c;
	int		start;

	i = -1;
	c = 0;
	start = 0;
	while (com[++i])
	{
		if (ft_strcmp(com[i], "|") == 0)
		{
			if (c == 0)
				list = creat_list(com, start, i, &c);
			else
				add_node(list, com, start, i);
			start = i + 1;
		}
	}
	if (c == 0)
		list = creat_list(com, start, i, &c);
	else if (c == 1)
		add_node(list, com, start, i);
	return (list);
}
