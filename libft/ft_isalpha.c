/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:18:57 by jmayou            #+#    #+#             */
/*   Updated: 2024/09/08 12:46:50 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
		return (1);
	else
		return (0);
}

//#include <stdio.h>
// int main() {
//    char c = 'A';
//
//    if (ft_isalpha(c)) {
//        %c is an alphabet character.\n", c);
//    } else {
//        printf("%c is not an alphabet character.\n", c);
//    }
//
//    return (0);
//}
