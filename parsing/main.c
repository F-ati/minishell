/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:58:50 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/24 13:47:09 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_strdup_arr(char **env, int n)
{
	int		len;
	int		i;
	char	**resu;

	len = ft_arry_len(env);
	i = 0;
	resu = ft_calloc(sizeof(char *), len + n);
	while (i < len)
	{
		resu[i] = ft_strdup(env[i]);
		i++;
	}
	if (n == 2)
		resu[i] = ft_strdup("?=0");
	return (resu);
}

void	init_shell(t_shell *minishell, char **env)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	minishell->env = ft_strdup_arr(env, 2);
	minishell->export = ft_strdup_arr(env, 1);
	g_signal = 0;
	minishell->data.c = 0;
	minishell->list = NULL;
}

void	ft_minishell(t_shell *minishell)
{
	t_list	*tmp;

	ft_search_variable(&minishell->data.com, minishell->env);
	fix_quotes(minishell->data.com);
	ft_join(minishell->data.com);
	ft_join_quote(minishell->data.com);
	minishell->data.command = ft_split_by_space(minishell->data.com);
	free_arr(minishell->data.com);
	minishell->data.c = check_error(minishell->data.command);
	if (minishell->data.c == 0)
	{
		minishell->list = ft_filling_list(minishell->data.command);
		tmp = minishell->list;
		ft_execution(minishell);
		minishell->list = tmp;
		free_list(minishell->list);
	}
	else if (minishell->data.c == 1)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		g_signal = 2;
	}
	free_arr(minishell->data.command);
}

int	sp_tb(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			count++;
		i++;
	}
	return (count);
}

// void	aa(void)
// {
// 	system("leaks -q minishell");
// }

int	main(int ac, char **av, char **env)
{
	t_shell	minishell;

	(void)ac;
	(void)av;
	init_shell(&minishell, env);
	while (1)
	{
		ft_update_exit_status_env(&minishell);
		if (minishell.data.input == NULL)
			break ;
		if (sp_tb(minishell.data.input) != ft_strlen(minishell.data.input))
		{
			minishell.data.com = ft_split_command(minishell.data.input,
					&g_signal);
			if (minishell.data.com)
				ft_minishell(&minishell);
		}
		update_exit_status_env(&minishell);
		g_signal = 0;
		add_history(minishell.data.input);
		free(minishell.data.input);
	}
	free_arr(minishell.env);
	free_arr(minishell.export);
	return (g_signal);
}
