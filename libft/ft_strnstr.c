/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:00:12 by jmayou            #+#    #+#             */
/*   Updated: 2024/01/12 16:19:47 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	f;

	i = 0;
	j = 0;
	if ((s2[0] == '\0'))
		return ((char *)s1);
	while (i < n && s1[i])
	{
		j = 0;
		f = i;
		while (f < n && s1[f] == s2[j] && s2[j])
		{
			f++;
			j++;
		}
		if (s2[j] == '\0')
			return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main ()
// {
// 	char *str = "oh no not the empty";

// 	printf ("%s\n", ft_strnstr(str, "no", 7));
// 	printf ("%s\n", strnstr(str, "no", 7));
// }
