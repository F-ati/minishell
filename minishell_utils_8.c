/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_8.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:08:05 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/24 13:29:15 by jmayou           ###   ########.fr       */
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
	(void)shell;
	while (j < nb)
	{
		if (j == nb - 1)
		{
			waitpid(child_pids[j], &status, 0);
			if (WIFEXITED(status))
				g_signal = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				signal_nb = WTERMSIG(status);
				g_signal = 128 + signal_nb;
			}
		}
		waitpid(child_pids[j], NULL, 0);
		j++;
	}
	signal(SIGINT, handle_sigint);
}

void	ft_execve(t_shell *shell, char *path)
{
	int	pid;
	int	status;
	int	signal_nb;

	signal (SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal (SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(path, shell->list->command, shell->env);
		perror("bash : execve");
		g_signal = 1;
		exit(g_signal);
	}
	waitpid(pid, &status, 0);
	signal (SIGINT, handle_sigint);
	if (WIFEXITED(status))
		g_signal = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		signal_nb = WTERMSIG(status);
		g_signal = 128 + signal_nb;
	}
}
