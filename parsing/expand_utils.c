/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:06:14 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/22 15:31:25 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	encryption(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
			str[i] = '\1';
		else if (str[i] == '>')
			str[i] = '\2';
		else if (str[i] == '|')
			str[i] = '\3';
		i++;
	}
}

void	initialize_data_of_replale(t_data_of_replace *data, char *command,
		char *var, char *value)
{
	data->i = 0;
	data->j = 0;
	data->len_val = ft_strlen(value);
	data->len_var = ft_strlen(var);
	data->len_all = ft_strlen(command) - data->len_var - 1 + data->len_val;
	data->what = 1;
}

char	*get_env_value(char **env, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strcmp_len(env[i], var, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*get_variable(char *command, int pos)
{
	char	*var;
	int		i;

	i = 0;
	while (command[i + pos])
	{
		if (ft_isalnum(command[i + pos]) == 0)
			break ;
		i++;
	}
	var = ft_substr(command, pos, i);
	return (var);
}

char	*ft_replace(char *command, char *var, char *value, int k)
{
	t_data_of_replace	data;

	initialize_data_of_replale(&data, command, var, value);
	data.resu = malloc(data.len_all + 1);
	while (command[data.i])
	{
		if (command[data.i] == '$' && data.what)
		{
			k = 0;
			while (value && (k < data.len_val))
				data.resu[data.j++] = value[k++];
			data.i += data.len_var;
			data.what = 0;
		}
		else
			data.resu[data.j++] = command[data.i];
		data.i++;
	}
	data.resu[data.j] = '\0';
	return (data.resu);
}
