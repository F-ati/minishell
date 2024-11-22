/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:28:04 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/20 20:39:00 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlcpy(char *dst, const char *s, size_t dsize)
// {
// 	size_t	i;

// 	i = 0;
// 	if (dsize == 0)
// 		return (ft_strlen(s));
// 	while (s[i] && i < dsize - 1)
// 	{
// 		dst[i] = s[i];
// 		i++;
// 	}
// 	dst[i] = 0;
// 	return (ft_strlen(s));
// }
//#include <stdio.h>
//#include <string.h>
// int main()
//{
//    char dest[20];
//    size_t len = ft_strlcpy(dest, "lorem ipsum", 3);
//    printf("%zu %s\n", len, dest);
//
//    char dest1[20];
//    len = strlcpy(dest1, "lorem ipsum", 3);
//    printf("%zu %s\n", len, dest1);
//
//}
