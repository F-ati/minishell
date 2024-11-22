/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:35:27 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/16 21:25:32 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	filling(char **resu, char *str, char **arry, int i)
{
	int	j;

	j = 0;
	if (str != NULL)
	{
		resu[i] = ft_strdup(str);
		i++;
	}
	else
	{
		while (arry[j])
		{
			resu[i] = ft_strdup(arry[j]);
			j++;
			i++;
		}
	}
	resu[i] = NULL;
	return (i);
}

void	ft_filling(char *s, char **s1, int lenf, int start)
{
	int	i;

	i = 0;
	while (i < lenf)
	{
		if (s[start] == '|' || s[start] == '<' || s[start] == '>')
		{
			(*s1)[i++] = ' ';
			(*s1)[i++] = s[start++];
			if ((s[start] == '<' || s[start] == '>') && s[start
				- 1] == s[start])
				(*s1)[i++] = s[start++];
			(*s1)[i] = ' ';
		}
		else
			(*s1)[i] = s[start++];
		i++;
	}
	(*s1)[i] = '\0';
}
