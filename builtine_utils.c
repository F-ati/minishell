/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtine_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:05:23 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/22 21:51:35 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd_env(t_shell *shell, char *old_pwd)
{
	int		j;
	char	*pwd;

	j = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		print_error(shell, old_pwd);
		return ;
	}
	while (shell->env[j] != NULL)
	{
		if (shell->env[j][0] == 'P' && strncmp(shell->env[j], "PWD", 3) == 0
			&& shell->env[j][3] == '=')
			ft_set_pwd_env(shell, pwd, j);
		if (shell->env[j][0] == 'O' && strncmp(shell->env[j], "OLDPWD", 6) == 0
			&& shell->env[j][6] == '=')
		{
			free(shell->env[j]);
			shell->env[j] = ft_strjoin("OLDPWD=", old_pwd);
		}
		j++;
	}
	free(old_pwd);
	free(pwd);
}

int	check_is_has_value(char *command)
{
	int	i;

	i = 0;
	while (command[i] != '\0')
	{
		if (command[i] == '=')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	**ft_resize(char **str, char *new_var)
{
	char	**p;
	int		len;

	len = ft_strnb(str);
	p = ft_calloc(sizeof(char *), (len + 2));
	if (p == NULL)
		return (NULL);
	len = 0;
	while (str[len] != NULL)
	{
		p[len] = str[len];
		len++;
	}
	p[len] = ft_strdup(new_var);
	len++;
	free(str);
	return (p);
}

char	*get_name_var(char *command)
{
	char	*p;
	int		i;

	i = 0;
	while (command[i] != '=' && command[i] != '\0')
	{
		i++;
	}
	p = malloc(sizeof(char) * (i + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (command[i] != '=' && command[i] != '\0')
	{
		p[i] = command[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	ft_apdate_env(t_shell *shell, char *new_arg)
{
	int		indix;
	char	*var_name;

	var_name = get_name_var(new_arg);
	indix = get_var_indix(shell->env, var_name);
	if (indix < 0)
	{
		shell->env = ft_resize(shell->env, new_arg);
	}
	else
	{
		free(shell->env[indix]);
		shell->env[indix] = ft_strdup(new_arg);
	}
	free(var_name);
}
