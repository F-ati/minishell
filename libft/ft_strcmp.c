/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:49:08 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/23 13:08:47 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
//#include <stdio.h>
//#include <string.h>
// int main ()
//{
//
//	printf ("%d\n",ft_strncmp("abcdefgh", "abcdwxyz", 4));
//	printf ("%d\n",strncmp("abcdefgh", "abcdwxyz", 4));
//	printf ("%d\n",ft_strncmp("\200", "\0", 1));
//	printf ("%d\n",strncmp("\200", "\0", 1));
//}
