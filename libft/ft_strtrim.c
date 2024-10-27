/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:09:22 by jmayou            #+#    #+#             */
/*   Updated: 2024/01/03 18:47:13 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*result;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	while (i < len)
	{
		if (ft_strchr(set, s1[i]) != NULL)
			i++;
		else
			break ;
	}
	while (i != len && len > 0)
	{
		if (ft_strchr(set, s1[len - 1]) != NULL)
			len--;
		else
			break ;
	}
	result = ft_substr(s1, i, len - i);
	return (result);
}

//#include <stdio.h>
// int main()
//{
//  printf("%s\n", ft_strtrim("mayouksszssma","ofg"));
//  return (0);
//}
// msa7 kelma ->xz<-