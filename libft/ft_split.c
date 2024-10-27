/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:41:28 by jmayou            #+#    #+#             */
/*   Updated: 2024/09/05 18:37:33 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	checkword(const char *str, char c)
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
		if (str[i] != c && what == 0)
		{
			word++;
			what = 1;
		}
		else if (str[i] == c)
			what = 0;
		i++;
	}
	return (word);
}

static void	*free_mem(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;
	int		start;

	i = 0;
	start = 0;
	j = 0;
	result = malloc(sizeof(char *) * (checkword(s, c) + 1));
	if (result == NULL)
		return (NULL);
	while (j < checkword(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		result[j] = ft_substr(s, start, i - start);
		if (result[j] == NULL)
			return (free_mem(result, j));
		j++;
	}
	result[j] = NULL;
	return (result);
}
// #include <stdio.h>
// int main()
// {
// 	char str[] = "jankanlanhgnkh";
// 	char c ='n';
// 	char **resu = ft_split(str , c);
// 	int i =  0;
// 	while (resu[i])
// 	{
// 		printf("%s\n", resu[i]);
// 		i++;
// 	}
// }