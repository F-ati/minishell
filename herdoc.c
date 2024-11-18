/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:09:05 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/18 16:01:37 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_write_data(int fd, char *value)
// {
// 	int	i;

// 	i = 0;
// 	if (value == NULL)
// 		return (i);
// 	while (value[i] != '\0')
// 	{
// 		write(fd, &value[i], 1);
// 		i++;
// 	}
// 	return (i);
// }

void	ft_print_var(t_shell *shell, char *str, int fd)
{
	char	*valid_var;
	char	*value;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\'' && str[i + 1] != ' ')
		{
			valid_var = get_variable(str, i + 1);
			len = ft_strlen(get_variable(str, i + 1));
			value = get_env_value(shell->env, valid_var);
			free(valid_var);
			ft_write_data(fd, value);
			i = len + 1;
		}
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
		str = readline(">");
		if (str == NULL)
			exit(0);
		if (strcmp(str, redir->file_name) == 0)
		{
			free(str);
			break ;
		}
		ft_print_var(shell, str, fd);
		write(fd, "\n", 1);
		free(str);
	}
}

int	ft_herdoc(t_shell *shell, t_dir *redir)
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open(redir->herdoc_file_name, O_RDWR | O_CREAT, 0777);
	if (fd < 0)
	{
		free(redir->herdoc_file_name);
		shell->exit_status = 1;
		return (-1);
	}
	if (redir->is_quoted == 1)
	{
		while (1)
		{
			str = readline(">");
			if (str == NULL)
				exit(0);
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
	else
		ft_expand_heredoc_vars(shell, redir, fd);
	free(redir->herdoc_file_name);
	return (fd);
}

char	*generate_temp_filename(char *file_name)
{
	file_name = ft_strjoin("/tmp/", file_name);
	while (access(file_name, F_OK) == 0)
	{
		file_name = my_strjoin(file_name, "1");
	}
	return (file_name);
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
