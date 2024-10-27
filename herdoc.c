/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:09:05 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/10/27 18:26:17 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int  ft_is_env_var(t_shell *shell ,char *str)
{
	int len;
	int i ;
	i = 0;
	len = ft_strlen(str);
	while ( shell->env[i] != NULL)
	{
		if (strncmp(shell->env[i],str,len) == 0 && shell->env[i][len] == '=' )
			return (i);
		i++;
	}
	return(-7);
}

void ft_herdoc(t_shell *shell)
{
	int fd ;
	char *str ;
	int i = 0;
	int indix ;
	int len ;
	
	fd = open("tmpfile.txt", O_RDWR | O_CREAT, 0666);
	if(shell->list->redir->is_quoted == 1)
	{
		while(1)
		{
			str = readline(">");
			if (str == NULL)
				exit(1);
			if(ft_strcmp(str,shell->list->redir->file_name) == 0)
				break;
			len = ft_strlen(str);
			i = 0;
			while(i < len)
			{
				write (fd,&str[i],1);
				i++;
			}
			write(fd,"\n",1);
		}
	}
	else
	{
		while(1)
		{
			str = readline(">");
			if (str == NULL)
				exit(1);
			if(strcmp(str , shell->list->redir->file_name) == 0)
				break;

			if(str[0] == '$')
			{
				char *varName = ft_strdup(&str[1]);
				indix = ft_is_env_var(shell, varName);
				if(indix >= 0)
				{
					len = ft_strlen(varName) + 1;
					while(shell->env[indix][len] != '\0')
					{
						write (fd,&shell->env[indix][len],1);
						len++;
				    }
				}
				write(fd,"\n",1);

			}
			else
			{
				len = ft_strlen(str);
				i = 0;
				while(i < len)
				{
					write (fd,&str[i],1);
					i++;
				}
				write(fd,"\n",1);
			}
			
		}
		
	}
}
