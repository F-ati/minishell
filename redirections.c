/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:44:05 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/08/12 11:41:35 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// implement ">"
void redirect_output( t_shell  *shell)
{
	int fd;
	fd = open(shell->list->redir->file_name , O_CREAT | O_RDWR  ,0644);
	if(fd < 0)
	{
		printf("minishell: %s: %s\n", shell->list->redir->file_name,strerror(errno));
		shell->exit_status = 1;
		return;
	}
	if (dup2(fd,STDOUT_FILENO) < 0)
	{
		printf("minishell: %s: %s\n", shell->list->redir->file_name,strerror(errno));
		close(fd);
		shell->exit_status = 1;
		return;
	}
    close(fd);
    
}

// implement "<"

void redirect_input( t_shell  *shell)
{
	int fd;
	
	
	    fd = open(shell->list->redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fd < 0)
		{
			printf("minishell: %s: %s\n", shell->list->redir->file_name,strerror(errno));
			shell->exit_status = 1;
			// return failure
			return;
		}
		if (dup2(fd,STDIN_FILENO) < 0)
		{
			printf("minishell: %s: %s\n", shell->list->redir->file_name,strerror(errno));
			close(fd);
			shell->exit_status = 1;
			// return failure
			return;
		}
		close(fd);
}

// implement ">>"
void redirect_append( t_shell  *shell)
{
	int fd;
	fd = open(shell->list->redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(fd < 0)
	{
		printf("minishell: %s: %s\n", shell->list->redir->file_name,strerror(errno));
		shell->exit_status = 1;
		return;
	}
	if (dup2(fd,STDOUT_FILENO) < 0)
	{
		printf("minishell: %s: %s\n", shell->list->redir->file_name,strerror(errno));
		close(fd);
		shell->exit_status = 1;
		return;
	}
    close(fd);
    
}