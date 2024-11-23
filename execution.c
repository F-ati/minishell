/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:58:09 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/23 13:56:46 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (str != NULL && shell->list->command[0])
		generate_exec_path(shell, flag, str);
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
		ft_cd(shell, cmmnd_len(shell->list->command));
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

void	execute_pipe_command(t_shell *shell, int nb)
{
	t_execution	*exec;

	exec = malloc(sizeof(t_execution));
	init_exec_var(exec, nb);
	while (shell->list != NULL)
	{
		init_var(shell);
		if (ft_open_redictions(shell) == -1)
		{
			ensure_fds_closed(shell->list);
			return ;
		}
		if (pipe_fork_and_execute(shell, nb, exec))
			return ;
	}
	if (exec->preve_fd != -1)
		close(exec->preve_fd);
	wait_all_children(shell, exec->child_pids, nb);
	signal(SIGINT, handle_sigint);
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
}


