/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_by_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:58:42 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/22 15:51:19 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	check_command(const char *str)
{
	int	i;
	int	word;
	int	what;

	i = 0;
	word = 0;
	what = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (is_space(str[i]) == 0 && what == 0)
		{
			word++;
			what = 1;
		}
		else if (is_space(str[i]) == 1)
			what = 0;
		i++;
	}
	return (word);
}

char	**ft_split_by_space_tab(char const *s)
{
	char	**result;
	int		i;
	int		j;
	int		start;

	i = 0;
	start = 0;
	j = 0;
	result = malloc(sizeof(char *) * (check_command(s) + 1));
	if (result == NULL)
		return (NULL);
	while (j < check_command(s))
	{
		while (s[i] && is_space(s[i]) == 1)
			i++;
		start = i;
		while (s[i] && is_space(s[i]) == 0)
			i++;
		result[j] = ft_substr(s, start, i - start);
		if (result[j] == NULL)
			return (free_arry(result, j));
		j++;
	}
	result[j] = NULL;
	return (result);
}

int	quote_in_start(char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i][0] != '"' && str[i][0] != '\'')
			count += check_command(str[i]);
		else
			count++;
		i++;
	}
	return (count);
}

char	**ft_split_by_space(char **str)
{
	char	**mini_str;
	char	**resu;
	int		i;
	int		count;
	int		j;

	i = 0;
	j = 0;
	count = quote_in_start(str);
	resu = malloc(sizeof(char *) * (count + 1));
	while (str[i])
	{
		if (str[i][0] != '"' && str[i][0] != '\'')
		{
			mini_str = ft_split_by_space_tab(str[i]);
			j = filling(resu, NULL, mini_str, j);
			free_arr(mini_str);
		}
		else
			j = filling(resu, str[i], NULL, j);
		i++;
	}
	return (resu);
}
