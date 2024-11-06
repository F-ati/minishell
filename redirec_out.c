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

void redirect_output( t_shell  *shell)
{
	int fd;
	int saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdout < 0) {
        printf("minishell: dup failed: %s\n", strerror(errno));
        shell->exit_status = 1;
        return;
    }
	if(access(shell->list->redir->file_name,F_OK) < 0)
		fd = open(shell->list->redir->file_name , O_CREAT | O_RDWR | O_TRUNC ,0777);
	else
		fd = open(shell->list->redir->file_name ,  O_RDWR | O_TRUNC ,0777);
	if(fd < 0)
	{
		printf("minishell: %s: %s\n", shell->list->redir->file_name,strerror(errno));
		shell->exit_status = 1;
		return;
		//  what is O_TEUNC AND WHY ????;
	}
	if (dup2(fd,STDOUT_FILENO) < 0)
	{
		printf("minishell: %s: %s\n", shell->list->redir->file_name,strerror(errno));
		close(fd);
		shell->exit_status = 1;
		return;
	}
	close(fd);
	execute_simple_command(shell);
	if (dup2(saved_stdout, STDOUT_FILENO) < 0) {
    printf("minishell: dup2 failed: %s\n", strerror(errno));
    shell->exit_status = 1;
    return;
    }

    close(saved_stdout);
}

