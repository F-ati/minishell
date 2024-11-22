/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtine_command_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:16:27 by root              #+#    #+#             */
/*   Updated: 2024/11/22 13:07:48 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	ft_cd(t_shell *shell)
{
	char	*path;
	int		args_nb;
	char	*old_pwd;

	args_nb = cmmnd_len(shell->list->command);
	if (args_nb == 1)
	{
		path = go_to_home(shell);
		if (path == NULL)
			return ;
	}
	else
		path = shell->list->command[1];
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
	{
		print_error(shell, old_pwd);
		return ;
	}
	if (chdir(path) < 0)
	{
		print_error(shell, old_pwd);
		return ;
	}
	shell->exit_status = 0;
	update_pwd_env(shell, old_pwd);
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

void	ft_apdate_export(t_shell *shell, char *new_arg)
{
	int		indix;
	char	*for_free;
	char	*var_name;

	var_name = get_name_var(new_arg);
	indix = get_var_indix(shell->export, var_name);
	if (indix < 0)
	{
		shell->export = ft_resize(shell->export, new_arg);
	}
	else
	{
		for_free = shell->export[indix];
		shell->export[indix] = ft_strdup(new_arg);
		free(for_free);
	}
	free(var_name);
}

void	print_exported_vars(t_shell *shell)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (shell->export[i] != NULL)
	{
		j = 0;
		flag = 0;
		ft_write_data(1, "declare -x ");
		while (shell->export[i][j] != '\0')
		{
			if (shell->export[i][j] == '\"' || shell->export[i][j] == '$')
			{
				write(1, "\\", 1);
			}
			write(1, &shell->export[i][j], 1);
			if (shell->export[i][j] == '=' && flag == 0)
			{
				write(1, "\"", 1);
				flag = 1;
			}
			j++;
		}
		if (flag == 1)
		{
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

void	ft_export(t_shell *shell)
{
	int	i;
	int	flag;

	flag = 0;
	if (shell->list->command[1] == NULL)
	{
		print_exported_vars(shell);
		shell->exit_status = 0;
		return ;
	}
	i = 1;
	while (shell->list->command[i] != NULL)
	{
		if (check_invalid_arg(shell->list->command[i]) == 1)
		{
			if (check_is_has_value(shell->list->command[i]) == 1)
			{
				ft_apdate_env(shell, shell->list->command[i]);
			}
			ft_apdate_export(shell, shell->list->command[i]);
			shell->exit_status = 0;
		}
		else
		{
			ft_printf("minishell: export: '%s': not a valid identifier\n",
				shell->list->command[i]);
			shell->exit_status = 1;
		}
		i++;
	}
}

// unset func

char	**remove_and_resize(char **str, int indx)
{
	int		len;
	char	**p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strnb(str);
	p = malloc(sizeof(char *) * len);
	if (p == NULL)
	{
		return (NULL);
	}
	while (str[i] != NULL)
	{
		if (i == indx)
		{
			free(str[i]);
			i++;
		}
		else
		{
			p[j] = str[i];
			j++;
			i++;
		}
	}
	p[j] = NULL;
	free(str);
	return (p);
}

void	ft_unset(t_shell *shell)
{
	int	indx1;
	int	indx2;
	int	i;

	i = 1;
	while (shell->list->command[i] != NULL)
	{
		if (check_invalid_arg(shell->list->command[i]) == 1)
		{
			indx1 = get_var_indix(shell->export, shell->list->command[i]);
			indx2 = get_var_indix(shell->env, shell->list->command[i]);
			if (indx1 >= 0)
				shell->export = remove_and_resize(shell->export, indx1);
			if (indx2 >= 0)
				shell->env = remove_and_resize(shell->env, indx2);
			shell->exit_status = 0;
		}
		else
		{
			ft_printf("minishell: unset: %s: not a valid identifier\n",
				shell->list->command[i]);
			shell->exit_status = 1;
		}
		i++;
	}
}
