/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_8.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:08:05 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/23 14:12:50 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
