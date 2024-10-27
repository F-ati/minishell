/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:39:44 by jmayou            #+#    #+#             */
/*   Updated: 2023/12/19 17:36:53 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

//#include <stdio.h>
//
// int main()
//{
//    char buffer[10] = "jamila";
//
//		printf ("Before : %s.\n", buffer);
//       ft_bzero(buffer, 10); // kol bit ki3mrb zero
//		printf ("After  : %s.\n", buffer);
//   		return (0);
//}
