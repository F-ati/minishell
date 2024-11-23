/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:07:29 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/23 21:04:31 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_write_data(int fd, char *value)
{
	int	i;

	i = 0;
	if (value == NULL)
		return (i);
	while (value[i] != '\0')
	{
		write(fd, &value[i], 1);
		i++;
	}
	return (i);
}

void	update_exit_status_env(t_shell *shell)
{
	char	*tmp[2];

	tmp[1] = ft_itoa(shell->exit_status);
	tmp[0] = ft_strjoin("?=", tmp[1]);
	ft_apdate_env(shell, tmp[0]);
	free(tmp[0]);
	free(tmp[1]);
}

char	*generate_temp_filename(char *file_name)
{
	file_name = ft_strjoin("/tmp/.", file_name);
	while (access(file_name, F_OK) == 0)
	{
		file_name = my_strjoin(file_name, "1");
	}
	return (file_name);
}

int	display_variable(t_shell *shell, char *str, int i, int fd)
{
	char	*valid_var;
	char	*value;
	int		len;

	len = 0;
	valid_var = get_variable(str, i + 1);
	len = ft_strlen(get_variable(str, i + 1));
	value = get_env_value(shell->env, valid_var);
	free(valid_var);
	ft_write_data(fd, value);
	return (len);
}

int	ft_handle_input_redirection(t_shell *shell, t_dir *redir)
{
	if (redir->type == HEREDOC)
	{
		close(shell->list->fd_input);
		shell->list->fd_input = open(redir->herdoc_file_name, O_RDWR, 0777);
		if (shell->list->fd_input == -1)
			return (-1);
	}
	else if (redir->type == IN)
	{
		close(shell->list->fd_input);
		shell->list->fd_input = ft_open_input(redir->file_name, shell);
		if (shell->list->fd_input == -1)
			return (-1);
	}
	return (1);
}
