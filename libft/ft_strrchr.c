/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:46:46 by jmayou            #+#    #+#             */
/*   Updated: 2023/12/31 11:24:13 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		i--;
	}
	return (0);
}

//#include <stdio.h>
//#include <string.h>
//
// int main() {
//	const char *str = "Hello, World!";
//	char target = 'o';
//
//	char *result = ft_strrchr(NULL, target);
//
//	printf ("%s\n", result);
//	return (0);
//}
