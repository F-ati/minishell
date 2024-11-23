/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtine_command_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:16:27 by root              #+#    #+#             */
/*   Updated: 2024/11/23 22:36:19 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_shell *shell, int args_nb)
{
	char	*path;
	char	*old_pwd;

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
	g_signal = 0;
	update_pwd_env(shell, old_pwd);
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
			check_export_cases(shell->export[i][j], &flag);
			j++;
		}
		if (flag == 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
}

void	ft_export(t_shell *shell)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (shell->list->command[1] == NULL)
	{
		print_exported_vars(shell);
		g_signal = 0;
		return ;
	}
	while (shell->list->command[i] != NULL)
	{
		if (check_invalid_arg(shell->list->command[i]) == 1)
		{
			if (check_is_has_value(shell->list->command[i]) == 1)
				ft_apdate_env(shell, shell->list->command[i]);
			ft_apdate_export(shell, shell->list->command[i]);
			g_signal = 0;
		}
		else
			export_invalid_arg_error(shell, shell->list->command[i]);
		i++;
	}
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
			g_signal = 0;
		}
		else
		{
			ft_printf("minishell: unset: %s: not a valid identifier\n",
				shell->list->command[i]);
			g_signal = 1;
		}
		i++;
	}
}
