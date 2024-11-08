/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:44:05 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/08 18:15:03 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// implement ">"
int  redirect_output( t_shell  *shell)
{
	int fd;
	fd = open(shell->list->redir->file_name , O_CREAT | O_RDWR  ,0644);
	if(fd < 0)
	{
		printf("minishell: %s: %s\n", shell->list->redir->file_name,strerror(errno));
		shell->exit_status = 1;
		return(1);
	}
	if (dup2(fd,STDOUT_FILENO) < 0)
	{
		printf("minishell: %s: %s\n", shell->list->redir->file_name,strerror(errno));
		close(fd);
		shell->exit_status = 1;
		return(1);
	}
    close(fd); 
	return (0);
}

// implement "<"

int  redirect_input( t_shell  *shell)
{
	int fd;
	
	
	    fd = open(shell->list->redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fd < 0)
		{
			printf("minishell: %s: %s\n", shell->list->redir->file_name,strerror(errno));
			shell->exit_status = 1;
			// return failure
			return(1);
		}
		if (dup2(fd,STDIN_FILENO) < 0)
		{
			printf("minishell: %s: %s\n", shell->list->redir->file_name,strerror(errno));
			close(fd);
			shell->exit_status = 1;
			// return failure
			return(1);
		}
		close(fd);
		return (0);
}

// implement ">>"
int  redirect_append( t_shell  *shell)
{
	int fd;
	fd = open(shell->list->redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(fd < 0)
	{
		printf("minishell: %s: %s\n", shell->list->redir->file_name,strerror(errno));
		shell->exit_status = 1;
		return(1);
	}
	if (dup2(fd,STDOUT_FILENO) < 0)
	{
		printf("minishell: %s: %s\n", shell->list->redir->file_name,strerror(errno));
		close(fd);
		shell->exit_status = 1;
		return(1);
	}
    close(fd);
	return (0);
}
void handel_redictions(t_shell *shell)
{
	t_list *save_list  = NULL;
	t_dir   *save_redir = NULL;

	save_list = shell->list;
	while(save_list != NULL)
	{
		save_redir = save_list->redir;
		while(save_redir != NULL)
		{
			if(save_redir->type == HEREDOC)
				save_redir = 
			save_redir = save_redir->next;
		}
		save_list = save_list->next;
	}
}