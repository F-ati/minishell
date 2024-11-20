/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtine_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:16:27 by root              #+#    #+#             */
/*   Updated: 2024/11/19 21:57:26 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo command

void	ft_print_str(t_shell *minishell, int flag)
{
	int	i;
	int	j;

	j = flag;
	while (minishell->list->command[j] != NULL)
	{
		i = 0;
		while (minishell->list->command[j][i] != '\0')
		{
			write(1, &minishell->list->command[j][i], 1);
			i++;
		}
		if (minishell->list->command[j + 1] != NULL)
			write(1, " ", 1);
		j++;
	}
	if (flag == 1)
		write(1, "\n", 1);
}

void	ft_echo(t_shell *shell)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (shell->list->command[j] != NULL && shell->list->command[j][i] == '-')
	{
		i++;
		while (shell->list->command[j][i] != '\0'
			&& shell->list->command[j][i] == 'n')
		{
			i++;
		}
		if (shell->list->command[j][i] == '\0')
		{
			j++;
			i = 0;
		}
		else
		{
			break ;
		}
	}
	ft_print_str(shell, j);
	shell->exit_status = 0;
}

//  env command

void	ft_env(t_shell *data)
{
	int	j;
	int	i;

	j = 0;
	while (data->env[j] != NULL)
	{
		i = 0;
		while (data->env[j][i] != '\0' && data->env[j][0] != '?')
		{
			// if(data->env[j][i] = '@' && data->env[j][i] == '')
			write(1, &data->env[j][i], 1);
			i++;
		}
		if (data->env[j][0] != '?')
			write(1, "\n", 1);
		j++;
	}
	data->exit_status = 0;
}

// pwd command ;
void	ft_pwd(t_shell *shell)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("minishell: pwd: getcwd");
		shell->exit_status = 1;
		return ;
	}
	ft_write_data(1, path);
	write(1, "\n", 1);
	shell->exit_status = 0;
	free(path);
}

// cd command

void	update_pwd_env(t_shell *shell, char *old_pwd)
{
	int		j;
	char	*pwd;

	j = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		free(old_pwd);
		perror("minishell: cd");
		shell->exit_status = 1;
	}
	while (shell->env[j] != NULL)
	{
		if (shell->env[j][0] == 'P' && strncmp(shell->env[j], "PWD", 3) == 0
			&& shell->env[j][3] == '=')
		{
			free(shell->env[j]);
			shell->env[j] = ft_strjoin("PWD=", pwd);
		}
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

void	ft_cd(t_shell *shell)
{
	char	*path;
	int		args_nb;
	char	*old_pwd;

	args_nb = cmmnd_len(shell->list->command);
	if (args_nb == 1)
	{
		path = get_env_value(shell->env, "HOME");
		if (path == NULL)
		{
			ft_printf("minishell: cd: HOME not set\n");
			shell->exit_status = 1;
			return ;
		}
	}
	else
	{
		path = shell->list->command[1];
	}
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
	{
		perror("minishell: cd");
		shell->exit_status = 1;
		return ;
	}
	if (chdir(path) < 0)
	{
		free(old_pwd);
		perror("minishell: cd");
		shell->exit_status = 1;
		return ;
	}
	shell->exit_status = 0;
	update_pwd_env(shell, old_pwd);
}
//  export command ;

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

void	ft_export(t_shell *shell)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 0;
	if (shell->list->command[1] == NULL)
	{
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

// exit func

void	ft_exit(t_shell *shell)
{
	int nb;
	int len;
	len = cmmnd_len(shell->list->command);
	if (len == 1)
	{
		exit(shell->exit_status);
	}
	if (len == 2 && ft_check_is_number(shell->list->command[1]) == 1)
	{
		nb = ft_atoi(shell->list->command[1]);
		exit(nb);
	}
	if (ft_check_is_number(shell->list->command[1]) == 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(shell->list->command[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		shell->exit_status = 255;
		exit(255);
	}
	if (ft_check_is_number(shell->list->command[1]) == 1 && len > 2)
	{
		shell->exit_status = 1;
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
	}
}