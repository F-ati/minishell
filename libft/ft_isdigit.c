/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:27:38 by jmayou            #+#    #+#             */
/*   Updated: 2023/12/09 13:14:29 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if ((c <= '9' && c >= '0'))
		return (1);
	else
		return (0);
}

//#include <stdio.h>
//#include <ctype.h>
//
// int main()
//{
//    char digit = '.';
//
//    printf ("isdigit	:	%d\n", isdigit(digit));
//    printf ("ft_isdigit :	%d\n", ft_isdigit(digit));
//}
