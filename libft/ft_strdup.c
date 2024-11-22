/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:52:43 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/22 15:41:22 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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
char	*ft_strdup_and_rm_nprintible(const char *s1)
{
	int		i;
	char	*dup;
	int		len;
	int	j;

	i = 0;
	j = 0;
	len = ft_strlen(s1);
	dup = ft_calloc(len + 1, sizeof(char));
	if (dup == NULL)
		return (0);
	while (i < len)
	{
		if(s1[i] != '\1')
		{
			dup[j] = s1[i];
			j++;
		}
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
