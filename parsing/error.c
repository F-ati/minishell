/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:30:10 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/23 22:02:27 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char *str)
{
	if (ft_strcmp(str, "<<") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str,
			">>") == 0 || ft_strcmp(str, ">") == 0)
		return (1);
	return (0);
}

int	ft_arry_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	check_error(char **command)
{
	int	len;
	int	i;

	i = 0;
	len = ft_arry_len(command);
	if (len == 0)
		return (2);
	if ((ft_strcmp(command[0], "|") == 0 || ft_strcmp(command[len - 1],
				"<") == 0 || ft_strcmp(command[len - 1], ">") == 0
			|| ft_strcmp(command[len - 1], "<<") == 0 || ft_strcmp(command[len
					- 1], ">>") == 0 || ft_strcmp(command[len - 1], "|") == 0))
		return (1);
	while (command[i + 1])
	{
		if (is_redirection(command[i]) == 1 && (is_redirection(command[i
						+ 1]) == 1 || ft_strcmp(command[i + 1], "|") == 0))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_last_word(char *str)
{
	char	*last_word;
	int		cout;
	int		len;

	cout = 0;
	len = ft_strlen(str);
	while (is_space(str[len - 1]) == 1)
	{
		len--;
		cout++;
	}
	while (len > 0 && is_space(str[len - 1]) == 0)
	{
		len--;
	}
	last_word = ft_substr(str, len, (ft_strlen(str) - cout) - len);
	return (last_word);
}

int	ft_check(char *str)
{
	int	i;
	int	k;
	int	xhal;

	i = 0;
	k = 0;
	xhal = 0;
	while (str[i] != '\'' && str[i] != '\"' && str[i])
		i++;
	if (str[i] == '\0')
		return (0);
	else
	{
		if (i != 0)
			xhal++;
		while (str[i])
		{
			k = position_of_quoter(str, i, &k, &xhal);
			if (k == -1)
				return (-1);
			i = k;
		}
	}
	return (xhal);
}
