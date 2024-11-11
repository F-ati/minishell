/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:44:05 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/11 12:44:52 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// open ">"
int  ft_open_output(char *file_name ,t_shell  *shell)
{
	int fd;
	fd = open(file_name , O_CREAT | O_RDWR | O_TRUNC ,0644);
	if(fd < 0)
	{
		printf("minishell: %s: %s\n",file_name,strerror(errno));
		shell->exit_status = 1;
		return(-1);
		// exit(1);
	}
	return (fd);
}

// open "<"

int  ft_open_input(char *file_name ,t_shell *shell)
{
	int fd;
	fd = open(file_name, O_RDWR, 0644);
	if(fd < 0 )
	{	
		printf("minishell: %s: %s\n", file_name, strerror(errno));
		shell->exit_status = 1;
		return(-1);
		// exit(1);
	}
	return (fd);
}

// open ">>"
int  ft_open_append(char *file_name , t_shell *shell)
{
	int fd;
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(fd < 0)
	{
		printf("minishell: %s: %s\n", file_name,strerror(errno));
		shell->exit_status = 1;
		return(-1);
		// exit(1);
	}
	return (fd);
}
int ft_open_redictions(t_shell *shell)
{
	t_list *save_list  = NULL;
	t_dir   *save_redir = NULL;

	save_list = shell->list;
	while(save_list != NULL)
	{
		save_redir = save_list->redir;
		while(save_redir != NULL)
		{
			if(save_redir->type == IN)
			{
				close(save_list->fd_input);
				save_list->fd_input = ft_open_input(save_redir->file_name ,shell);
				if(save_list->fd_input == -1)
					return(-1);
			}
			if(save_redir->type == OUT)
			{
				close(save_list->fd_output);
				save_list->fd_output = ft_open_output(save_redir->file_name ,shell);
				if(save_list->fd_output == -1)
					return(-1);
			}
			if(save_redir->type == APPEND)
			{
				close(save_list->fd_output);
				save_list->fd_output = ft_open_append(save_redir->file_name,shell);
				if(save_list->fd_input == -1)
					return(-1);
			}
			if(save_redir->type == HEREDOC)
			{
				close(save_list->fd_input);
				save_list->fd_input = save_list->fd_heredoc;
				if(save_list->fd_input == -1)
					return(-1);
			}
			save_redir = save_redir->next;
		}
		save_list = save_list->next;
	}
	return(1);
} 