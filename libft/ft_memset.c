/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:57:31 by jmayou            #+#    #+#             */
/*   Updated: 2024/01/01 17:05:41 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	int buffer[] = {5000012, 15, 44, 2};
// 	int i = 0;
// 	ft_memset(buffer+3, 0 ,sizeof(int));
// 	ft_memset(buffer+3, 13 ,sizeof(char));
// 	while ( i < 4)
// 	{
// 		printf ("%d\n", buffer[i]);
// 		i++;
// 	}
//  	return (0);
// }
