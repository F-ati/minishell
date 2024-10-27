/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:23:22 by jmayou            #+#    #+#             */
/*   Updated: 2023/12/09 17:25:25 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c <= 'Z' && c >= 'A')
	{
		c = c + 32;
	}
	return (c);
}

//#include <stdio.h>
//#include <ctype.h>
//
// int main()
//{
//    int ch = 'A';
//    char Ch = ft_tolower(ch);
//
//    printf("Original character: %c\n", ch);
//    printf("Uppercase character: %c\n", Ch);
//
//    return (0);
//}
