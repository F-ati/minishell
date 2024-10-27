/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:52:43 by jmayou            #+#    #+#             */
/*   Updated: 2024/03/07 11:11:01 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dup;
	int		len;

	i = 0;
	len = ft_strlen(s1);
	dup = ft_calloc(len + 1, sizeof(char));
	if (dup == NULL)
		return (0);
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	return (dup);
}
//#include <string.h>
//#include <stdio.h>
//
// int main() {
//    char *original = NULL;
//    char *duplicate = ft_strdup(original);
//       printf("**** %s\n", duplicate);
//}
