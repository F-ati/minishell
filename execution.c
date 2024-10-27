/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:58:09 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/10/27 18:25:00 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_access(t_shell *minishell)
{
	minishell->i = 0;

	char *str;
	str = getenv("PATH");
	if (str == NULL)
    {

		return (-7);
	}
	
		minishell->path = ft_split(str ,':');

	while(minishell->path[minishell->i] != NULL)
	{
		minishell->path[minishell->i] = ft_strjoin(minishell->path[minishell->i],"/");
		minishell->path[minishell->i] = ft_strjoin(minishell->path[minishell->i] , minishell->list->command[0]);
		minishell->i++;
	}
	minishell->i = 0;
	while(minishell->path[minishell->i] != NULL)
	{
		if (access(minishell->path[minishell->i] , X_OK) == 0)
			return(1);
		minishell->i++;
	}
	return (-7);
}

void ft_exec_func(t_shell *minishell)
{
	int  pid ;
	if (check_access(minishell) == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(minishell->path[minishell->i], minishell->list->command,minishell->env);
			//  tcheck the error if execve failed whid perror;
		}
		else
		{
			wait(NULL);
		}
	}
	else
	{
		printf("command not found\n");
	}
}

void ft_is_builtins(t_shell *minishell)
{
	
		if(ft_strcmp("echo",minishell->list->command[0]) == 0)
		{
			ft_echo(minishell);
		}
		else if (ft_strcmp("cd",minishell->list->command[0]) == 0)
		{
			//  cd | cd ~ | cd ..;
			//  if the pwd is unset ;
			//  set the pwd in env when run the cd ;
			ft_cd(minishell);
		}
		else if ( ft_strcmp("pwd",minishell->list->command[0]) == 0 )
		{
			ft_pwd(minishell);
		}
		else if ( ft_strcmp("export",minishell->list->command[0]) == 0)
		{
			// what happing when I run export HOME=
			ft_export(minishell);
		}
		else if (ft_strcmp("unset",minishell->list->command[0]) == 0 )
		{
			minishell->exit_status = 0;
			ft_unset(minishell);
		}
		else if ( ft_strcmp("env",minishell->list->command[0]) == 0)
		{
			// WHEN DESPLAY FERST TIME THE EV DON'T DESPLAY THE OLDPWD;
			ft_env(minishell);
		}
		else if (ft_strcmp("exit",minishell->list->command[0]) == 0)
		{
			ft_exit(minishell);
		}
		
	   else 
		{ 
			ft_exec_func(minishell);
		}
	
}

void ft_execution(t_shell *minishell)
{
	minishell->cmd_nb = ft_cmnd_nb(minishell->list);
	minishell->herdoc_nb = ft_herdoc_nb(minishell->list);
	if (minishell->cmd_nb == 1)
	{
		while(minishell->herdoc_nb > 0)
		{
			ft_herdoc(minishell);
			minishell->herdoc_nb--;
		}
		// skeep rederections;
		// der kol func l rederct mohadd 
		// and after hendle hadxi f builtin and call this func inside it ;
		ft_is_builtins(minishell);
		
	}
	
}

