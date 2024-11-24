/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:47:28 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/24 13:29:03 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_fork_and_execute(t_shell *shell, int nb, t_execution *exec)
{
	if (pipe(exec->fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	exec->id = fork();
	if (exec->id == -1)
	{
		perror("fork");
		return (1);
	}
	if (exec->id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_ps(exec, nb, shell);
	}
	else
		parent_ps(exec, shell);
	return (0);
}

void	init_exec_var(t_execution *exec, int nb)
{
	exec->child_pids = malloc(sizeof(int) * nb);
	exec->fd[0] = -1;
	exec->fd[1] = -1;
	exec->preve_fd = -1;
	exec->id = -1;
	exec->i = 0;
}

void	parent_ps(t_execution *exec, t_shell *shell)
{
	exec->child_pids[exec->i] = exec->id;
	if (exec->preve_fd != -1)
		close(exec->preve_fd);
	exec->preve_fd = exec->fd[0];
	close(exec->fd[1]);
	if (shell->list->fd_input != -1)
		close(shell->list->fd_input);
	if (shell->list->fd_output != -1)
		close(shell->list->fd_output);
	shell->list = shell->list->next;
	exec->i++;
}

void	child_ps(t_execution *exec, int nb, t_shell *shell)
{
	if (exec->i == 0)
	{
		if (dup2(exec->fd[1], 1) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	else if (exec->i < nb - 1)
	{
		if (dup2(exec->preve_fd, 0) == -1 || dup2(exec->fd[1], 1) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	else if (dup2(exec->preve_fd, 0) == -1)
	{
		perror("dup2");
		exit(1);
	}
	re_dup_redirection(shell);
	closing_fds(shell, exec);
	execute_command(shell, 1);
	exit(g_signal);
}

void	closing_fds(t_shell *shell, t_execution *exec)
{
	close(shell->list->fd_input);
	close(shell->list->fd_output);
	close(exec->fd[0]);
	close(exec->fd[1]);
	if (exec->preve_fd != -1)
		close(exec->preve_fd);
}
