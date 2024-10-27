/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:15:51 by jmayou            #+#    #+#             */
/*   Updated: 2024/09/08 12:46:46 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(char c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') || (c <= '9'
			&& c >= '0') || (c == '_'))
		return (1);
	else
		return (0);
}

//#include <stdio.h>
// int main()
//{
//    char c = 'A';
//
//	if (ft_isalnum(c))
//	{
//        %c yes\n", alphaNumChar);
//    } else {
//        printf("%c no \n", alphaNumChar);
//    }
//}
