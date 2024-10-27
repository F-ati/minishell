/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:37:46 by jmayou            #+#    #+#             */
/*   Updated: 2023/12/31 10:55:23 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && i < n - 1)
		i++;
	return (str1[i] - str2[i]);
}
//#include <stdio.h>
//#include <string.h>
//
// int main() {
//    char str1[] = "abcdefghij";
//    char str2[] = "abcdefgxyz";
//
//    int result1 = memcmp(str1, str2, 7);
//    int result2 = ft_memcmp(str1, str2, 7);
//
//	printf("%d %d\n", result1, result2);
//
//    return (0);
//}
