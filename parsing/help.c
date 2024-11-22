/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:41:30 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/22 15:45:56 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fix_quotes(char **str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		len = ft_strlen(str[i]);
		if (str[i][0] == '\'')
		{
			str[i][0] = '\"';
			while (len >= 0)
			{
				if (str[i][len] == '\'')
				{
					str[i][len] = '\"';
					break ;
				}
				len--;
			}
		}
	}
}

int	ft_strcmp_len(char *s1, char *s2, int len)
{
	int	i;

	i = 0;
	while (i < len && s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	}
	if (i == len)
		return (0);
	return (s1[i] - s2[i]);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	ft_close(char *str, char c, int n, int start)
{
	int	i;

	i = start + 1;
	if (n == 1)
	{
		while (str[i] && str[i] != c)
			i++;
		if (str[i] == c)
			return (i + 1);
	}
	else if (n == 0)
	{
		while (str[i] && str[i] != c)
			i++;
		if (str[i] == c)
			return (i);
		else if (str[i] == '\0')
			return (i);
	}
	return (-1);
}

char	*ft_substr_add_space(char *s, int start, int len)
{
	char	*s1;
	int		i;
	int		lenf;
	int		size;

	size = 1;
	i = -1;
	lenf = len;
	while (++i < len)
	{
		if (s[start + i] == '|' || size == 2 || (s[start + i] == '<' && s[start
					+ i + 1] != '<') || (s[start + i] == '>' && s[start + i
					+ 1] != '>'))
		{
			lenf += 2;
			size = 1;
		}
		else if ((s[start + i] == '<' && s[start + i + 1] == '<') || (s[start
					+ i] == '>' && s[start + i + 1] == '>'))
			size += 1;
	}
	s1 = malloc((lenf + 1) * sizeof(char));
	ft_filling(s, &s1, lenf, start);
	return (s1);
}
