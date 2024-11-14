/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:09:05 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/14 00:47:09 by fel-aziz         ###   ########.fr       */
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

int ft_herdoc( t_shell *shell,t_dir *redir)
{
	int fd ;
	char *str ;
	int i = 0;
	int indix ;
	int len ;
	fd = open(redir->herdoc_file_name, O_RDWR | O_CREAT, 0777);
	if(fd < 0)
	{
		perror("herdoc");
		shell->exit_status = 1;
		return(-1);
	}
	if(redir->is_quoted == 1)
	{
		while(1)
		{
			str = readline(">");
			if (str == NULL)
				exit(11);
			if(ft_strcmp(str,redir->file_name) == 0)
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
			{
				printf("helll\n");
				exit(44);
			}
			if(strcmp(str , redir->file_name) == 0)
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
	return (fd);
}
char *generate_temp_filename(char *file_name)
{
	file_name = ft_strjoin("/tmp/",file_name);
	while(access(file_name ,F_OK) == 0)
	{
		file_name = ft_strjoin(file_name,"1");
	}
	return(file_name);
}
void handle_heredoc(t_shell *shell)
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
			{
				save_redir->herdoc_file_name = generate_temp_filename(save_redir->file_name);
				close(save_list->fd_heredoc);
				save_list->fd_heredoc = ft_herdoc( shell,save_redir);
				// pause();
			}
			save_redir = save_redir->next;
		}
		save_list = save_list->next;
	}
}

