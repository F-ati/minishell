/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:58:09 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/22 12:18:18 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_exec_non_builtin(t_shell *shell, int flag)
{
	int		i;
	char	*str;
	char	**path;

	i = 0;
	str = NULL;
	path = NULL;
	str = get_env_value(shell->env, "PATH");
	if (access(shell->list->command[0], F_OK | X_OK) == 0)
	{
		if (flag == 0)
			ft_execve(shell, shell->list->command[0]);
		else
			execve(shell->list->command[0], shell->list->command, shell->env);
	}
	else if (str == NULL || ft_check_is_exist(shell->list->command[0],
			'/') == 1)
	{
		ft_printf("minishell: %s: No such file or directory\n",
			shell->list->command[0]);
		shell->exit_status = 127;
	}
	else if (str != NULL)
	{
		path = ft_split(str, ':');
		while (path[i] != NULL)
		{
			path[i] = my_strjoin(path[i], "/");
			path[i] = my_strjoin(path[i], shell->list->command[0]);
			if (access(path[i], F_OK | X_OK) == 0)
			{
				if (flag == 0)
					ft_execve(shell, path[i]);
				else
					execve(path[i], shell->list->command, shell->env);
				break ;
			}
			i++;
		}
		if (ft_check_is_exist(shell->list->command[0], '/') == 1
			&& path[i] == NULL)
		{
			ft_printf("minishell: %s : No such file or directory\n",
				shell->list->command[0]);
			shell->exit_status = 127;
		}
		else if (path[i] == NULL)
		{
			ft_printf("minishell: %s: command not found\n",
				shell->list->command[0]);
			shell->exit_status = 127;
		}
		free_arr(path);
	}
}

void	execute_command(t_shell *shell, int flag)
{
	if (!shell->list->command[0])
		return ;
	if (ft_strcmp("echo", shell->list->command[0]) == 0)
		ft_echo(shell);
	else if (ft_strcmp("env", shell->list->command[0]) == 0)
		ft_env(shell);
	else if (ft_strcmp("pwd", shell->list->command[0]) == 0)
		ft_pwd(shell);
	else if (ft_strcmp("cd", shell->list->command[0]) == 0)
		ft_cd(shell);
	else if (ft_strcmp("export", shell->list->command[0]) == 0)
		ft_export(shell);
	else if (ft_strcmp("unset", shell->list->command[0]) == 0)
		ft_unset(shell);
	else if (ft_strcmp("exit", shell->list->command[0]) == 0)
		ft_exit(shell);
	else
		ft_exec_non_builtin(shell, flag);
}

void	ft_execut_simple_command(t_shell *shell)
{
	int	original_stdin;
	int	original_stdout;

	original_stdin = dup(0);
	original_stdout = dup(1);
	if (shell->list->fd_input != -1)
	{
		dup2(shell->list->fd_input, 0);
		close(shell->list->fd_input);
	}
	if (shell->list->fd_output != -1)
	{
		dup2(shell->list->fd_output, 1);
		close(shell->list->fd_output);
	}
	execute_command(shell, 0);
	dup2(original_stdin, 0);
	dup2(original_stdout, 1);
	close(original_stdin);
	close(original_stdout);
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

void	execute_pipe_command(t_shell *shell, int nb)
{
	int	preve_fd;
	int	fd[2];
	int	id;
	int	child_pids[nb];
	int	i;

	fd[0] = -1;
	fd[1] = -1;
	preve_fd = -1;
	id = -1;
	i = 0;
	while (shell->list != NULL)
	{
		init_var(shell);
		if (ft_open_redictions(shell) == -1)
		{
			ensure_fds_closed(shell->list);
			return ;
		}
		pipe(fd);
		id = fork();
		if (id == 0)
		{
			if (i == 0)
			{
				dup2(fd[1], 1);
			}
			else if (i < nb - 1)
			{
				dup2(preve_fd, 0);
				dup2(fd[1], 1);
			}
			else
			{
				dup2(preve_fd, 0);
			}
			if (shell->list->fd_input != -1)
			{
				dup2(shell->list->fd_input, 0);
				close(shell->list->fd_input);
			}
			if (shell->list->fd_output != -1)
			{
				dup2(shell->list->fd_output, 1);
				close(shell->list->fd_output);
			}
			close(shell->list->fd_input);
			close(shell->list->fd_output);
			close(fd[0]);
			close(fd[1]);
			if (preve_fd != -1)
				close(preve_fd);
			execute_command(shell, 1);
			exit(shell->exit_status);
		}
		else
		{
			child_pids[i] = id;
			if (preve_fd != -1)
				close(preve_fd);
			preve_fd = fd[0];
			close(fd[1]);
			if (shell->list->fd_input != -1)
				close(shell->list->fd_input);
			if (shell->list->fd_output != -1)
				close(shell->list->fd_output);
			shell->list = shell->list->next;
			i++;
		}
	}
	if (preve_fd != -1)
		close(preve_fd);
	wait_all_children(shell, child_pids, nb);
}
void	ft_execution(t_shell *shell)
{
	int	redir_ret;
	int	nb;

	redir_ret = 0;
	init_var(shell);
	handle_heredoc(shell);
	redir_ret = ft_open_redictions(shell);
	nb = ft_cmnd_nb(shell->list);
	if (redir_ret < 0)
	{
		ensure_fds_closed(shell->list);
		return ;
	}
	else if (nb == 1)
	{
		ft_execut_simple_command(shell);
	}
	else
	{
		execute_pipe_command(shell, nb);
	}
	update_exit_status_env(shell);
	// unlink(save_redir->herdoc_file_name); ===> to do
}
