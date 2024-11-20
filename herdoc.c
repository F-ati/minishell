/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:09:05 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/20 11:56:10 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_variable(t_shell *shell, char *str, int fd)
{
	char	*value;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			value = get_env_value(shell->env, "?");
			ft_write_data(fd, value);
			i++;
		}
		else if (str[i] == '$' && str[i + 1] != ' ')
		{
			len = display_variable(shell, str, i, fd);
			i = len + 1;
		}
		else
			write(fd, &str[i], 1);
		i++;
	}
}

void	ft_expand_heredoc_vars(t_shell *shell, t_dir *redir, int fd)
{
	char	*str;

	str = NULL;
	while (1)
	{
		str = readline("> ");
		if (str == NULL)
			break ;
		if (strcmp(str, redir->file_name) == 0)
		{
			free(str);
			break ;
		}
		find_variable(shell, str, fd);
		write(fd, "\n", 1);
		free(str);
	}
}

void	ft_unexpanded_heredoc_vars(t_dir *redir, int fd)
{
	char	*str;

	str = NULL;
	while (1)
	{
		str = readline("> ");
		if (str == NULL)
			break ;
		if (ft_strcmp(str, redir->file_name) == 0)
		{
			free(str);
			break ;
		}
		ft_write_data(fd, str);
		write(fd, "\n", 1);
		free(str);
	}
}

int	ft_herdoc(t_shell *shell, t_dir *redir)
{
	int	fd;
	int	id;

	fd = open(redir->herdoc_file_name, O_TRUNC | O_RDWR | O_CREAT, 0644);
	if (fd < 0)
	{
		unlink(redir->herdoc_file_name);
		free(redir->herdoc_file_name);
		return (-1);
	}
	id = fork();
	if (id == 0)
	{
		if (redir->is_quoted == 1)
			ft_unexpanded_heredoc_vars(redir, fd);
		else
			ft_expand_heredoc_vars(shell, redir, fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(NULL);
	}
	return (fd);
}

void	handle_heredoc(t_shell *shell)
{
	t_list	*save_list;
	t_dir	*save_redir;

	save_list = NULL;
	save_redir = NULL;
	save_list = shell->list;
	while (save_list != NULL)
	{
		save_redir = save_list->redir;
		while (save_redir != NULL)
		{
			if (save_redir->type == HEREDOC)
			{
				save_redir->herdoc_file_name = generate_temp_filename("ab");
				close(save_list->fd_heredoc);
				save_list->fd_heredoc = ft_herdoc(shell, save_redir);
			}
			save_redir = save_redir->next;
		}
		save_list = save_list->next;
	}
}
