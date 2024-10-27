/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:55:28 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/08/12 11:21:59 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_open( t_data  *data)
{
	int fd = open(data->info->name_file, O_CREAT | O_RDWR  ,777);
	
	if (fd  >= 0)
	{
		int nfd ;
	 	nfd = dup2(fd, STDIN_FILENO);
		

	// close(fd);
	char str[11] ;
	read(nfd,str, 9);
	str[10] = '\0';
	printf("%s\n",str);
	// ft_env(data);
	// printf("--->%d",fd);	
	}
}