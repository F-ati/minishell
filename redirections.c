/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:44:05 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/19 18:14:40 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_output(char *file_name, t_shell *shell)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_printf("minishell: %s: %s\n", file_name, strerror(errno));
		shell->exit_status = 1;
		return (-1);
	}
	return (fd);
}

int	ft_open_input(char *file_name, t_shell *shell)
{
	int	fd;

	fd = open(file_name, O_RDWR, 0644);
	if (fd < 0)
	{
		ft_printf("minishell: %s: %s\n", file_name, strerror(errno));
		shell->exit_status = 1;
		return (-1);
	}
	return (fd);
}

int	ft_open_append(char *file_name, t_shell *shell)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_printf("minishell: %s: %s\n", file_name, strerror(errno));
		shell->exit_status = 1;
		return (-1);
	}
	return (fd);
}

int	ft_open_redictions(t_shell *shell)
{
	t_dir	*save_redir;

	save_redir = shell->list->redir;
	while (save_redir != NULL)
	{
		if (save_redir->type == IN)
		{
			close(shell->list->fd_input);
			shell->list->fd_input = ft_open_input(save_redir->file_name, shell);
			if (shell->list->fd_input == -1)
				return (-1);
		}
		if (save_redir->type == OUT)
		{
			close(shell->list->fd_output);
			shell->list->fd_output = ft_open_output(save_redir->file_name,shell);
			if (shell->list->fd_output == -1)
				return (-1);
		}
		if (save_redir->type == APPEND)
		{
			close(shell->list->fd_output);
			shell->list->fd_output = ft_open_append(save_redir->file_name,shell);
			if (shell->list->fd_output == -1)
				return (-1);
		}
		if (save_redir->type == HEREDOC)
		{
			close(shell->list->fd_input);
			shell->list->fd_input = open(save_redir->herdoc_file_name, O_RDWR,0777);
			if (shell->list->fd_input == -1)
				return (-1);
		}
		save_redir = save_redir->next;
	}
	return (1);
}
