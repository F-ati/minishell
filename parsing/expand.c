/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:46:58 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/22 15:36:31 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_data_of_search_variable(t_data_for_expand *data, int n)
{
	if (n == 0)
	{
		data->i = -1;
		data->in = 0;
	}
	else
	{
		free(data->var);
		data->in = 1;
	}
}

int	can_replace(char **command, int i, int j)
{
	char	*tmp;
	char	*tmp1;
	char	*sub;

	sub = ft_substr(command[i], 0, j);
	tmp = ft_last_word(sub);
	if (i > 0)
		tmp1 = ft_last_word(command[i - 1]);
	else
		tmp1 = ft_last_word(command[0]);
	if (command[i][j] == '$' && j == 1 && is_quote(command[i][0]) == 1
		&& ft_strcmp(tmp1, "<<") == 0)
	{
		free_for_can_replace(&tmp, &tmp1, &sub);
		return (1);
	}
	else if (command[i][j] == '$' && (j > 1 && ft_strcmp(tmp, "<<") == 0))
	{
		free_for_can_replace(&tmp, &tmp1, &sub);
		return (1);
	}
	free_for_can_replace(&tmp, &tmp1, &sub);
	return (0);
}

void	hendled_expand(t_data_for_expand *data, char **env, char ***command)
{
	if ((*command)[data->i][data->j + 1] == '?')
	{
		data->value = get_env_value(env, "?");
		data->tmp = ft_replace((*command)[data->i], "?", data->value, 0);
		data->in = 1;
	}
	else if (((*command)[data->i][data->j + 1] == '@'
			|| ft_isdigit((*command)[data->i][data->j + 1]) == 1))
	{
		data->var = ft_substr((*command)[data->i], data->j + 1, 1);
		data->j += 1;
		data->tmp = ft_replace((*command)[data->i], data->var, "", 0);
		initialize_data_of_search_variable(data, 1);
	}
	else if ((*command)[data->i][data->j + 1] != ' ')
	{
		data->var = get_variable((*command)[data->i], data->j + 1);
		data->j += ft_strlen(data->var);
		data->value = get_env_value(env, data->var);
		if (data->value != NULL)
			encryption(data->value);
		data->tmp = ft_replace((*command)[data->i], data->var, data->value, 0);
		initialize_data_of_search_variable(data, 1);
	}
}

void	expand_command(t_data_for_expand *data, char ****command)
{
	data->in = 0;
	free((**command)[data->i]);
	(**command)[data->i] = data->tmp;
	data->len = ft_strlen((**command)[data->i]);
}

void	ft_search_variable(char ***command, char **env)
{
	t_data_for_expand	data;

	initialize_data_of_search_variable(&data, 0);
	while ((*command)[++data.i])
	{
		data.len = ft_strlen((*command)[data.i]);
		if ((*command)[data.i][0] != '\'')
		{
			data.j = -1;
			while (++data.j < data.len)
			{
				if ((*command)[data.i][data.j] == '$')
				{
					if (can_replace((*command), data.i, data.j) == 0)
					{
						hendled_expand(&data, env, command);
						if (data.in == 1)
							expand_command(&data, &command);
					}
				}
			}
		}
	}
}
