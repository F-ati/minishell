/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:02:41 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/22 21:41:42 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_indix(char **exp_or_env, char *name_var)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(name_var);
	while (exp_or_env[j] != NULL)
	{
		if ((exp_or_env[j][0] == name_var[0] && ft_strcmp(exp_or_env[j], name_var) == 0) && (exp_or_env[j][len] == '='
				|| exp_or_env[j][len] == '\0'))
		{
			return (j);
		}
		j++;
	}
	return (-7);
}

int	ft_check_is_number(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	if ((str[i] == '-' || str[i] == '+') && (str[i + 1] != '\0'))
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		i++;
	if (i == len)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	cmmnd_len(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	check_invalid_arg(char *command)
{
	int	i;

	if ((command[0] >= 'a' && command[0] <= 'z') || (command[0] >= 'A'
			&& command[0] <= 'Z') || (command[0] == '_'))
	{
		i = 1;
		while (command[i] != '\0' && command[i] != '=')
		{
			if ((command[i] < 'a' || command[i] > 'z') && (command[i] < 'A'
					|| command[i] > 'Z') && (command[i] < 48 || command[i] > 57)
				&& (command[i] != '_'))
			{
				return (-7);
			}
			i++;
		}
	}
	else
	{
		return (-7);
	}
	return (1);
}

char	*my_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		result[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	free(s1);
	return (result);
}
