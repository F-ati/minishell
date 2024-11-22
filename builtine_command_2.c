/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtine_command_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:32:40 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/22 12:37:14 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_str(t_shell *minishell, int flag)
{
	int	i;
	int	j;

	j = flag;
	while (minishell->list->command[j] != NULL)
	{
		i = 0;
		while (minishell->list->command[j][i] != '\0')
		{
			write(1, &minishell->list->command[j][i], 1);
			i++;
		}
		if (minishell->list->command[j + 1] != NULL)
			write(1, " ", 1);
		j++;
	}
	if (flag == 1)
		write(1, "\n", 1);
}

void	ft_echo(t_shell *shell)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (shell->list->command[j] != NULL && shell->list->command[j][i] == '-')
	{
		i++;
		while (shell->list->command[j][i] != '\0'
			&& shell->list->command[j][i] == 'n')
		{
			i++;
		}
		if (shell->list->command[j][i] == '\0')
		{
			j++;
			i = 0;
		}
		else
		{
			break ;
		}
	}
	ft_print_str(shell, j);
	shell->exit_status = 0;
}

void	ft_env(t_shell *data)
{
	int	j;
	int	i;

	j = 0;
	while (data->env[j] != NULL)
	{
		i = 0;
		while (data->env[j][i] != '\0' && data->env[j][0] != '?')
		{
			write(1, &data->env[j][i], 1);
			i++;
		}
		if (data->env[j][0] != '?')
			write(1, "\n", 1);
		j++;
	}
	data->exit_status = 0;
}

void	ft_pwd(t_shell *shell)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("minishell: pwd: getcwd");
		shell->exit_status = 1;
		return ;
	}
	ft_write_data(1, path);
	write(1, "\n", 1);
	shell->exit_status = 0;
	free(path);
}

void	ft_exit(t_shell *shell)
{
	int	nb;
	int	len;

	len = cmmnd_len(shell->list->command);
	if (len == 1)
		exit(shell->exit_status);
	if (len == 2 && ft_check_is_number(shell->list->command[1]) == 1)
	{
		nb = ft_atoi(shell->list->command[1]);
		exit(nb);
	}
	if (ft_check_is_number(shell->list->command[1]) == 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(shell->list->command[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		shell->exit_status = 255;
		exit(255);
	}
	if (ft_check_is_number(shell->list->command[1]) == 1 && len > 2)
	{
		shell->exit_status = 1;
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
	}
}
