/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:59:55 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/23 22:38:01 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_file_not_found(t_shell *shell, char *str)
{
	(void)shell;
	ft_printf("minishell: %s : No such file or directory\n", str);
	g_signal = 127;
}

void	print_cmd_not_found(t_shell *shell, char *str)
{
	(void)shell;
	ft_printf("minishell: %s: command not found\n", str);
	g_signal = 127;
}

void	is_fork_required(int flag, t_shell *shell, char *path)
{
	if (flag == 0)
		ft_execve(shell, path);
	else
		execve(path, shell->list->command, shell->env);
}

void	generate_exec_path(t_shell *shell, int flag, char *str)
{
	char	**path;
	int		i;

	i = -1;
	if (shell->list->command[0][0] == '\0')
	{
		print_cmd_not_found(shell, shell->list->command[0]);
		return ;
	}
	path = ft_split(str, ':');
	while (path[++i] != NULL)
	{
		path[i] = my_strjoin(path[i], "/");
		path[i] = my_strjoin(path[i], shell->list->command[0]);
		if (access(path[i], F_OK | X_OK) == 0)
		{
			is_fork_required(flag, shell, path[i]);
			break ;
		}
	}
	if (ft_check_is_exist(shell->list->command[0], '/') == 1 && path[i] == NULL)
		print_file_not_found(shell, shell->list->command[0]);
	else if (path[i] == NULL)
		print_cmd_not_found(shell, shell->list->command[0]);
	free_arr(path);
}

void	init_var(t_shell *shell)
{
	shell->list->fd_heredoc = -1;
	shell->list->fd_input = -1;
	shell->list->fd_output = -1;
}
