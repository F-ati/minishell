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

void ft_openfile( t_shell  *shell)
{
	int fd = open(shell->list->redir->file_name , O_CREAT | O_RDWR | O_TRUNC ,777);
	
	if (fd >= 0)
	{
		 dup2(fd, STDOUT_FILENO);
		
	}
	close(fd);
	printf("%d\n",fd);
}

void ft_openfile1( t_shell  *shell)
{
	int fd = open(shell->list->redir->file_name, O_CREAT | O_RDWR | O_APPEND ,777);
	if (fd >= 0)
	{
			int nfd;
			nfd = dup2(fd, STDOUT_FILENO);
		write(nfd,"a",1);
		printf("%d\n",fd);
		printf("lsdjfklhsad\n");
	}
}
