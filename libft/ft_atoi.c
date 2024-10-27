/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 13:27:41 by jmayou            #+#    #+#             */
/*   Updated: 2024/07/22 20:49:56 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	k;
	int	nb;

	i = 0;
	nb = 0;
	k = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	k = i;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	i = k;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		nb = (nb * 10) + (str[i++] - '0');
	return (nb);
}
// #include <stdio.h>
// #include <stdlib.h>
// int main()
// {
// 	const char *str = "+123";
// 	//int num = atoi(str);
// 	int num2 = ft_atoi(str);

// 	printf("%d \n", num2);
// 	return (0);
// }
