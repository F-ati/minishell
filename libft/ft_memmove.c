/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:32:23 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/22 21:24:57 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst == 0 && src == 0)
		return (NULL);
	else if (dst > src)
	{
		while (len != 0)
		{
			len--;
			((char *)dst)[len] = ((char *)src)[len];
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
//    char str1[] = "Hello, World!";
//    printf(" %s\n", ft_memmove(str1 , str1 + 4 ,4));
//    printf(" %s\n", memmove(str1 , str1 + 4 ,4));
// 	return (0);
// }
