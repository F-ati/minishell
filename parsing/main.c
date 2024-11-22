/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:58:50 by jmayou            #+#    #+#             */
/*   Updated: 2024/11/20 17:41:48 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // just print
void	printer(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		printf("--%s--\n", a[i++]);
}
void	print_list(t_list *list)
{
	while (list)
	{
		printer(list->command);
		while (list->redir)
		{
			if (list->redir->type)
				printf("redir type : %d and redir type : %s is_quated = %d\n",
					list->redir->type, list->redir->file_name,
					list->redir->is_quoted);
			list->redir = list->redir->next;
		}
		list = list->next;
	}
}
// end //
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
//
void	init_shell(t_shell *minishell, char **env)
{
	minishell->env = ft_strdup_arr(env, 2);
	minishell->export = ft_strdup_arr(env, 1);
	minishell->exit_status = 0;
	minishell->data.c = 0;
	minishell->list = NULL;
}

void	leak(void)
{
	system("leaks -q minishell");
}

void	ft_minishell(t_shell *minishell)
{
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
		// print_list (minishell->list);
		ft_execution(minishell);
		free_list(minishell->list);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		minishell->exit_status = 2;
	}
	free_arr(minishell->data.command);
}
int	count_space_tab(char *str)
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
int	main(int ac, char **av, char **env)
{
	t_shell	minishell;

	//   atexit(leak);
	(void)ac;
	(void)av;
	init_shell(&minishell, env);
	while (1)
	{
		minishell.data.input = readline("minishell$ ");
		if (minishell.data.input == NULL)
			break ;
		if (count_space_tab(minishell.data.input) != ft_strlen(minishell.data.input))
		{
			minishell.data.com = ft_split_command(minishell.data.input,
					&minishell.exit_status);
			if (minishell.data.com)
				ft_minishell(&minishell);
		}
		add_history(minishell.data.input);
		free(minishell.data.input);
	}
	free_arr(minishell.env);
	free_arr(minishell.export);
	return (minishell.exit_status);
}
