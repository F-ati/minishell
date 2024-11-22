/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_by_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:31:59 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/22 15:50:54 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_for_split_quote(t_data_for_split_quote *data)
{
	data->count = 0;
	data->quote_char = '\0';
	data->start = 0;
	data->in_quote = 0;
	data->i = 0;
}

void	beginning_not_quote(t_data_for_split_quote *data, char *str,
		char ***command)
{
	if (data->i > data->start)
		(*command)[data->count++] = ft_substr_add_space(str, data->start,
				data->i - data->start);
	data->in_quote = 1;
	data->quote_char = str[data->i];
	data->start = data->i;
}

void	ft_split_quote(char *str, char ***command)
{
	t_data_for_split_quote	data;

	initialize_for_split_quote(&data);
	while (str[data.i] != '\0')
	{
		if (is_quote(str[data.i]) == 1)
		{
			if (data.in_quote == 1 && str[data.i] == data.quote_char)
			{
				data.in_quote = 0;
				(*command)[data.count++] = ft_substr(str, data.start, data.i
						- data.start + 1);
				data.start = data.i + 1;
			}
			else if (data.in_quote == 0)
				beginning_not_quote(&data, str, command);
		}
		data.i++;
	}
	if (data.i > data.start)
		(*command)[data.count++] = ft_substr_add_space(str, data.start, data.i
				- data.start);
	(*command)[data.count] = NULL;
}

int	position_of_quoter(char *str, int i, int *k, int *xhal)
{
	if (str[i] == '\'')
		(*k) = ft_close(str, '\'', 1, i);
	else if (str[i] == '\"')
		(*k) = ft_close(str, '\"', 1, i);
	else if (str[i] != '\'' && str[i] != '\"')
	{
		if (ft_close(str, '\'', 0, i) <= ft_close(str, '\"', 0, i))
			(*k) = ft_close(str, '\'', 0, i);
		else
			(*k) = ft_close(str, '\"', 0, i);
	}
	if ((*k) != -1)
		(*xhal)++;
	return ((*k));
}

char	**ft_split_command(char *str, int *n)
{
	char	**command;
	int		len;

	if (str[0] == '\0')
		return (NULL);
	len = ft_check(str);
	if (len == -1)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching\n",
			2);
		(*n) = 2;
		return (NULL);
	}
	else if (len == 0)
	{
		command = malloc(sizeof(char *) * 2);
		command[0] = ft_substr_add_space(str, 0, ft_strlen(str));
		command[1] = NULL;
	}
	else
	{
		command = malloc(sizeof(char *) * (len + 1));
		ft_split_quote(str, &command);
	}
	return (command);
}
