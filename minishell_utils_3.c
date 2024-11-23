/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:59:55 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/22 21:53:41 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_file_not_found(t_shell *shell, char *str)
{
	ft_printf("minishell: %s : No such file or directory\n", str);
	shell->exit_status = 127;
}

void	print_cmd_not_found(t_shell *shell, char *str)
{
	ft_printf("minishell: %s: command not found\n", str);
	shell->exit_status = 127;
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

void	wait_all_children(t_shell *shell, int *child_pids, int nb)
{
	int	status;
	int	signal_nb;
	int	j;

	status = 0;
	signal_nb = 0;
	j = 0;
	while (j < nb)
	{
		if (j == nb - 1)
		{
			waitpid(child_pids[j], &status, 0);
			if (WIFEXITED(status))
			{
				shell->exit_status = WEXITSTATUS(status);
			}
			if (WIFSIGNALED(status))
			{
				signal_nb = WTERMSIG(status);
				shell->exit_status = 128 + signal_nb;
			}
		}
		waitpid(child_pids[j], NULL, 0);
		j++;
	}
}

void	ft_execve(t_shell *shell, char *path)
{
	int	pid;
	int	status;
	int	signal_nb;

	pid = fork();
	if (pid == 0)
	{
		execve(path, shell->list->command, shell->env);
		perror("bash : execve");
		shell->exit_status = 1;
		exit(shell->exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			shell->exit_status = WEXITSTATUS(status);
		}
		if (WIFSIGNALED(status))
		{
			signal_nb = WTERMSIG(status);
			shell->exit_status = 128 + signal_nb;
		}
	}
}