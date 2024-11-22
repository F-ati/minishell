/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:43:00 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/21 13:25:49 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_collect_in_first(char **next, char **str)
{
	int		len_next;
	int		len_word;
	char	*word;
	char	*new_next;
	char	*new_str;

	word = get_last_word((*str));
	len_word = ft_strlen(word);
	len_next = ft_strlen((*next));
	new_next = malloc(len_next + len_word + 1);
	new_next[0] = (*next)[0];
	ft_strcpy(new_next + 1, word);
	ft_strcpy(new_next + (1 + len_word), (*next) + 1);
	free((*next));
	(*next) = new_next;
	free(word);
	new_str = ft_remove((*str), len_word, 1);
	free((*str));
	(*str) = new_str;
}
void	ft_collect_in_last(char **next, char **str)
{
	int		len_next;
	int		len_word;
	char	*word;
	char	*new_next;
	char	*new_str;

	word = get_first_word((*str));
	len_word = ft_strlen(word);
	len_next = ft_strlen((*next));
	new_next = malloc(len_next + len_word + 1);
	ft_strcpy(new_next, (*next));
	ft_strcpy(new_next + (len_next - 1), word);
	new_next[len_next + len_word - 1] = (*next)[len_next - 1];
	new_next[len_next + len_word] = '\0';
	free((*next));
	(*next) = new_next;
	free(word);
	new_str = ft_remove((*str), len_word, 0);
	free((*str));
	(*str) = new_str;
}
void	edit_after_collect(char **str, int i)
{
	free(str[i]);
	while (str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = NULL;
}
char	**ft_join(char **str)
{
	int	i;
	int	len;

	i = 0;
	while (str[i] && str[i + 1])
	{
		len = ft_strlen(str[i]);
		if (is_space_or_quote(str[i][len - 1]) == 0 && (str[i + 1][0] == '\''
				|| str[i + 1][0] == '\"'))
		{
			ft_collect_in_first(&str[i + 1], &str[i]);
			if (ft_strcmp(str[i], "\0") == 0)
				edit_after_collect(str, i);
		}
		else if ((str[i][len - 1] == '\'' || str[i][len - 1] == '\"')
				&& is_space_or_quote(str[i + 1][0]) == 0)
		{
			ft_collect_in_last(&str[i], &str[i + 1]);
			if (ft_strcmp(str[i + 1], "\0") == 0)
				edit_after_collect(str, i + 1);
		}
		i++;
	}
	return (str);
}
void	ft_join_quote(char **str)
{
	int		i;
	int		len_str;
	int		len_next;
	char	*new_str;

	i = 0;
	while (str[i] && str[i + 1])
	{
		len_str = strlen(str[i]);
		len_next = strlen(str[i + 1]);
		if ((str[i][len_str - 1] == '\'' || str[i][len_str - 1] == '\"')
				&& (str[i + 1][0] == '\'' || str[i + 1][0] == '\"'))
		{
			new_str = malloc(len_str + len_next - 1);
			ft_strcpy(new_str, str[i]);
			ft_strcpy(new_str + len_str - 1, str[i + 1] + 1);
			free(str[i]);
			str[i] = new_str;
			edit_after_collect(str, i + 1);
			i = -1;
		}
		i++;
	}
}
