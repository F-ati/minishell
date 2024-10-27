/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:55:37 by jmayou            #+#    #+#             */
/*   Updated: 2023/12/09 17:20:28 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c <= 'z' && c >= 'a')
	{
		c = c - 32;
	}
	return (c);
}

//#include <stdio.h>
//#include <ctype.h>
//
// int main()
//{
//    int ch = 'A';
//    char Ch = ft_toupper(ch);
//
//    printf("Original character: %c\n", ch);
//    printf("Uppercase character: %c\n", Ch);
//
//    return (0);
//}
//
