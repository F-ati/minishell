/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:58:09 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/09 19:03:16 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_execve(t_shell *shell,char *path)
{
	int pid ;
	int status ;
	int signal_nb;
	pid = fork();
	if(pid == 0)
	{
		execve(path,shell->list->command,shell->env);
		perror("bash : execve");
		shell->exit_status = 1;
	}
	else
	{
		waitpid(pid,&status,0);
        if(WIFEXITED(status))
        {
            shell->exit_status = WEXITSTATUS(status);
        }
        if(WIFSIGNALED(status))
        {
            signal_nb =  WTERMSIG(status) ;
            shell->exit_status = 128 + signal_nb;
        }
    }
}

void ft_exec_non_builtin(t_shell *shell)
{
	int i = 0;	
	char *str ;
	char **path;
	str = get_env_value(shell->env, "PATH");
	if (access(shell->list->command[0] , F_OK | X_OK) == 0)
	{
		ft_execve(shell,shell->list->command[0]);
	}
	else if ( str == NULL || ft_check_is_exist(shell->list->command[0],'/') == 1)
	{
		printf("bash: %s: No such file or directory\n",shell->list->command[0]);
		shell->exit_status = 127;
		// return or not en depend 3la fayen m3ayta l functions ;
	}
	else if (str != NULL)
	{
		path = ft_split(str,':');
		while(path[i] != NULL)
		{
			path[i] = ft_strjoin(path[i],"/");
			path[i] = ft_strjoin(path[i],shell->list->command[0]);
			if(access(path[i], F_OK | X_OK) == 0)
			{
				ft_execve(shell,path[i]);
				break;
			}
			i++;
		}
		if(ft_check_is_exist(shell->list->command[0],'/') == 1 && path[i] == NULL)
		{
			// perror("bash");
			printf("bash: %s : No such file or directory\n",shell->list->command[0]);
			shell->exit_status = 127;
		}
		else if (path[i] == NULL)
		{
			printf("%s: command not found\n" ,shell->list->command[0]);
			shell->exit_status = 127;
		}
	}
	
}

void execute_simple_command(t_shell *shell)
{
	if (!shell->list->command[0])
		return ;
	if(ft_strcmp("echo",shell->list->command[0]) == 0)
	{
		ft_echo(shell);
	}
	else if ( ft_strcmp("env",shell->list->command[0]) == 0)
	{
		ft_env(shell);
	}
	else if ( ft_strcmp("pwd",shell->list->command[0]) == 0 )
	{
		ft_pwd(shell);
	}
	else if (ft_strcmp("cd",shell->list->command[0]) == 0)
	{
		//  cd ~ ;		
		ft_cd(shell);
	}
	else if ( ft_strcmp("export",shell->list->command[0]) == 0)
	{
		ft_export(shell);
	}
	else if (ft_strcmp("unset",shell->list->command[0]) == 0 )
	{
		ft_unset(shell);
	}
	else if (ft_strcmp("exit",shell->list->command[0]) == 0)
	{
		ft_exit(shell);
	}	
	else 
	{ 
		ft_exec_non_builtin(shell);
	}
	
}

void ft_execution(t_shell *shell)
{
	
	shell->list->fd_heredoc = 0;
	shell->list->fd_input = 0;
	shell->list->fd_output = 1;
	int original_stdin = dup(0);
    int original_stdout = dup(1);
	// close (0);
	// handle_heredoc(shell);
	ft_open_redictions(shell);
	// pid_t pid;
	// if ((pid = fork()) == 0)
	// {
		while(shell->list != NULL)
		{
			int  i = 0;
			i++;
			dprintf (2, "for %d : \n", i);
			// if(shell->list->fd_input != -1)
			// {
			// 	dup2(shell->list->fd_input,0);
			// 	close(shell->list->fd_input);
			// }
			// if(shell->list->fd_output != -1)
			// {
			// 	dup2(shell->list->fd_output , 1);
			// 	close(shell->list->fd_output);
			// }
			execute_simple_command(shell);
			
			shell->list = shell->list->next;
		}
	// }
	// wait (NULL);
	dup2(original_stdin, 0);
    dup2(original_stdout, 1);
}



