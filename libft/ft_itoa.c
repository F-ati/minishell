/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:00:59 by jmayou            #+#    #+#             */
/*   Updated: 2024/01/07 13:49:21 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	flong(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	if (n < 0)
	{
		n = (-1) * n;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int num)
{
	int		i;
	char	*result;

	i = flong(num);
	if (num == -2147483648)
		return (ft_strdup("-2147483648"));
	result = malloc((i + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	result[i] = '\0';
	i--;
	if (num == 0)
		result[0] = 48;
	if (num < 0)
	{
		num = (-1) * num;
		result[0] = '-';
	}
	while (num > 0)
	{
		result[i] = (num % 10) + 48;
		i--;
		num = num / 10;
	}
	return (result);
}

// #include <limits.h>
// #include <stdio.h>
// int main ()
// {
// 	int i = ;
// 	printf ("%s\n", ft_itoa(i));
// }
