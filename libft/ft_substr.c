/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:39:44 by jmayou            #+#    #+#             */
/*   Updated: 2024/06/07 14:11:54 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, int start, int len)
{
	int		i;
	char	*s1;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	if ((start + len) > ft_strlen(s))
		len = ft_strlen(s) - start;
	s1 = malloc((len + 1) * sizeof(char));
	if (s1 == NULL)
		return (0);
	while (i < len)
	{
		s1[i] = s[start + i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
//# include <stdio.h>
// int main ()
//{
//	char *str = "FULL BULLSHIT";
//	unsigned int b;
//	size_t len;
//
//	b = 400;
//	len = 20;
//	printf ("%s\n", ft_substr(str, b, len));
//}
