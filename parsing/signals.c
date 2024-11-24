/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:11:07 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/24 13:47:26 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sigint)
{
	(void)sigint;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 1;
}

void	ft_update_exit_status_env(t_shell *minishell)
{
	minishell->data.input = readline("minishell$ ");
	if (g_signal == 1)
	{
		update_exit_status_env(minishell);
		g_signal = 0;
	}
}
