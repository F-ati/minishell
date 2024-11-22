/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:05:23 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/22 13:13:23 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd_env(t_shell *shell, char *old_pwd)
{
	int		j;
	char	*pwd;

	j = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		print_error(shell, old_pwd);
		return ;
	}
	while (shell->env[j] != NULL)
	{
		if (shell->env[j][0] == 'P' && strncmp(shell->env[j], "PWD", 3) == 0
			&& shell->env[j][3] == '=')
		{
			free(shell->env[j]);
			shell->env[j] = ft_strjoin("PWD=", pwd);
		}
		if (shell->env[j][0] == 'O' && strncmp(shell->env[j], "OLDPWD", 6) == 0
			&& shell->env[j][6] == '=')
		{
			free(shell->env[j]);
			shell->env[j] = ft_strjoin("OLDPWD=", old_pwd);
		}
		j++;
	}
	free(old_pwd);
	free(pwd);
}