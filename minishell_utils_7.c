/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_7.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:15:07 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/22 21:54:44 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_output_redirection(t_shell *shell, t_dir *redir)
{
	if (redir->type == OUT)
	{
		close(shell->list->fd_output);
		shell->list->fd_output = ft_open_output(redir->file_name, shell);
		if (shell->list->fd_output == -1)
			return (-1);
	}
	else if (redir->type == APPEND)
	{
		close(shell->list->fd_output);
		shell->list->fd_output = ft_open_append(redir->file_name, shell);
		if (shell->list->fd_output == -1)
			return (-1);
	}
	return (1);
}

char	**remove_and_resize(char **str, int indx)
{
	char	**p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	p = malloc(sizeof(char *) * ft_strnb(str));
	if (p == NULL)
		return (NULL);
	while (str[i] != NULL)
	{
		if (i == indx)
			free(str[i++]);
		else
			p[j++] = str[i++];
	}
	p[j] = NULL;
	free(str);
	return (p);
}

void	re_dup_redirection(t_shell *shell)
{
	if (shell->list->fd_input != -1)
	{
		if (dup2(shell->list->fd_input, 0) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(shell->list->fd_input);
	}
	if (shell->list->fd_output != -1)
	{
		if (dup2(shell->list->fd_output, 1) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(shell->list->fd_output);
	}
}

void	ft_free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		free(path[i]);
		i++;
	}
}

void	check_export_cases(char c, int *flag)
{
	if (c == '\"' || c == '$')
		write(1, "\\", 1);
	write(1, &c, 1);
	if (c == '=' && *flag == 0)
	{
		write(1, "\"", 1);
		*flag = 1;
	}
}
