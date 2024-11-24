/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:12:13 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/24 12:58:46 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_shell *shell, char *old_pwd)
{
	(void)shell;
	free(old_pwd);
	perror("minishell: cd");
	g_signal = 1;
}

char	*go_to_home(t_shell *shell)
{
	char	*path;

	path = get_env_value(shell->env, "HOME");
	if (path == NULL)
	{
		ft_printf("minishell: cd: HOME not set\n");
		g_signal = 1;
		return (NULL);
	}
	return (path);
}

void	ensure_fds_closed(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		if (tmp->fd_heredoc >= 0)
		{
			close(tmp->fd_heredoc);
			tmp->fd_heredoc = -1;
		}
		if (tmp->fd_input >= 0)
		{
			close(tmp->fd_input);
			tmp->fd_input = -1;
		}
		if (tmp->fd_output >= 0)
		{
			close(tmp->fd_output);
			tmp->fd_output = -1;
		}
		tmp = tmp->next;
	}
}

void	ft_set_pwd_env(t_shell *shell, char *pwd, int j)
{
	free(shell->env[j]);
	shell->env[j] = ft_strjoin("PWD=", pwd);
}

void	export_invalid_arg_error(t_shell *shell, char *str)
{
	(void)shell;
	ft_printf("minishell: export: '%s': not a valid identifier\n", str);
	g_signal = 1;
}
