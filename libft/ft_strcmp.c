/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:49:08 by jmayou            #+#    #+#             */
/*   Updated: 2024/06/07 12:19:24 by jmayou           ###   ########.fr       */
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
