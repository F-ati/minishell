/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:52:53 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/16 17:54:28 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_strcpy(char *s1, char *s2)
{
	int i = 0;
	
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

int is_space_or_quote(char c) 
{
    return (c == ' ' || c == '\t' || c == '\'' || c == '\"');
}

char *ft_remove(char *str,int len_r, int n)
{
    int i;
    int j;
    int len;
    int len_s;
    char *resu;

    len_s = ft_strlen(str);
    len = len_s - len_r + 1;
    resu = malloc(len);
    i  = 0;
    if(n == 1)
    {
        i = -1;
        while(++i < len - 1)
            resu[i] = str[i];
    }
    else if(n == 0)
    {
        i = len_r;
        j = 0;
        while(j < len - 1)
            resu[j++] = str[i++];
        i = j;
    }
    resu[i] = '\0';
    return(resu);
}
char *get_last_word(char *str) 
{
    char *last_word;
    int len = ft_strlen(str);
    while (len > 0 && !is_space(str[len - 1]))
    {
        len--;
    }
    last_word = ft_strdup(&str[len]);
    return last_word;
}

char *get_first_word(char *str) 
{
    int len = 0;
    int i = 0;
    while (str[len] && !is_space(str[len])) {
        len++;
    }
    char *word = (char *)malloc(len + 1);
    while(i < len)
    {
        word[i] = str[i];
        i++;
    }
     word[i] = '\0';
    return word;
}