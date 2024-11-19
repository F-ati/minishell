/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:08:34 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/19 18:23:08 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_is_exist(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_free_env(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

int	ft_cmnd_nb(t_list *data)
{
	t_list	*tmp;
	int		i;

	tmp = data;
	i = 0;
	if (data == NULL)
	{
		return (0);
	}
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_herdoc_nb(t_list *save)
{
	int		i;
	t_dir	*redir_cur;
	t_list	*cur;

	i = 0;
	cur = save;
	if (save == NULL)
		return (0);
	while (cur != NULL)
	{
		redir_cur = cur->redir;
		while (redir_cur != NULL)
		{
			if (redir_cur->type == HEREDOC)
			{
				i++;
			}
			redir_cur = redir_cur->next;
		}
		cur = cur->next;
	}
	return (i);
}

int	ft_strnb(char **str)
{
	int	j;

	j = 0;
	while (str[j] != NULL)
	{
		j++;
	}
	return (j);
}

int	get_var_indix(char **exp_or_env, char *name_var)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(name_var);
	while (exp_or_env[j] != NULL)
	{
		if ((exp_or_env[j][0] == name_var[0] && strncmp(exp_or_env[j], name_var,
			len) == 0) && (exp_or_env[j][len] == '='
				|| exp_or_env[j][len] == '\0'))
		{
			return (j);
		}
		j++;
	}
	return (-7);
}

int	ft_check_is_number(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	if ((str[i] == '-' || str[i] == '+') && (str[i + 1] != '\0'))
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		i++;
	if (i == len)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	cmmnd_len(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	check_invalid_arg(char *command)
{
	int	i;

	if ((command[0] >= 'a' && command[0] <= 'z') || (command[0] >= 'A'
			&& command[0] <= 'Z') || (command[0] == '_'))
	{
		i = 1;
		while (command[i] != '\0' && command[i] != '=')
		{
			if ((command[i] < 'a' || command[i] > 'z') && (command[i] < 'A'
					|| command[i] > 'Z') && (command[i] < 48 || command[i] > 57)
				&& (command[i] != '_'))
			{
				return (-7);
			}
			i++;
		}
	}
	else
	{
		return (-7);
	}
	return (1);
}

char	*my_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		result[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	free(s1);
	return (result);
}

void	ft_free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		free(path[i]);
		i++;
	}
}

int	ft_write_data(int fd, char *value)
{
	int	i;

	i = 0;
	if (value == NULL)
		return (i);
	while (value[i] != '\0')
	{
		write(fd, &value[i], 1);
		i++;
	}
	return (i);
}
