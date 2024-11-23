/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:44:05 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/23 13:15:56 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_output(char *file_name, t_shell *shell)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		// ft_printf("minishell: %s: %s\n", file_name, strerror(errno));
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
		// ft_printf("minishell: %s: %s\n", file_name, strerror(errno));
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
		// ft_printf("minishell: %s: %s\n", file_name, strerror(errno));
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
		if (save_redir->type == IN || save_redir->type == HEREDOC)
		{
			if (ft_handle_input_redirection(shell, save_redir) == -1)
				return (-1);
		}
		else if (save_redir->type == OUT || save_redir->type == APPEND)
		{
			if (ft_handle_output_redirection(shell, save_redir) == -1)
				return (-1);
		}
		save_redir = save_redir->next;
	}
	return (1);
}
