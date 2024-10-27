/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 09:04:52 by jmayou            #+#    #+#             */
/*   Updated: 2023/12/09 13:12:59 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if ((c <= 126 && c >= 32))
		return (1);
	else
		return (0);
}

//#include <stdio.h>
//
// int main()
//{
//    char ch = '(';
//    if (ft_isascii(ch)) {
//        printf("yes \n");
//    } else {
//        printf("no \n");
//    }
//    return (0);
//}
