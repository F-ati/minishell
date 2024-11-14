/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:58:09 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/14 05:13:31 by fel-aziz         ###   ########.fr       */
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

void ft_exec_non_builtin(t_shell *shell , int flag)
{
	int i = 0;	
	char *str  = NULL;
	char **path = NULL;
	str = get_env_value(shell->env, "PATH");
	if (access(shell->list->command[0] , F_OK | X_OK) == 0)
	{
		if(flag == 0)
			ft_execve(shell,shell->list->command[0]);
		else
			execve(shell->list->command[0],shell->list->command , shell->env);
	}
	else if ( str == NULL || ft_check_is_exist(shell->list->command[0],'/') == 1)
	{
		printf("bash: %s: No such file or directory\n",shell->list->command[0]);
		shell->exit_status = 127;

	}
	else if (str != NULL)
	{
		path = ft_split(str,':');
		while(path[i] != NULL)
		{
			path[i] = my_strjoin(path[i],"/");
			path[i] = my_strjoin(path[i],shell->list->command[0]);
			if(access(path[i], F_OK | X_OK) == 0)
			{
				if(flag == 0)
					ft_execve(shell,path[i]);
				else
					execve(path[i] , shell->list->command,shell->env);
				break;
			}
			i++;
		}
		if(ft_check_is_exist(shell->list->command[0],'/') == 1 && path[i] == NULL)
		{
			printf("bash: %s : No such file or directory\n",shell->list->command[0]);
			shell->exit_status = 127;
		}
		else if (path[i] == NULL)
		{
			printf("%s: command not found\n" ,shell->list->command[0]);
			shell->exit_status = 127;
		}
	free_arr(path);
	}
}

void execute_command(t_shell *shell , int flag)
{
	if (!shell->list->command[0])
		return ;
	if(ft_strcmp("echo",shell->list->command[0]) == 0)
		ft_echo(shell);
	else if ( ft_strcmp("env",shell->list->command[0]) == 0)
		ft_env(shell);
	else if ( ft_strcmp("pwd",shell->list->command[0]) == 0 )
		ft_pwd(shell);
	else if (ft_strcmp("cd",shell->list->command[0]) == 0)
	{
		//  cd ~ ;		
		ft_cd(shell);
	}
	else if ( ft_strcmp("export",shell->list->command[0]) == 0)
		ft_export(shell);
	else if (ft_strcmp("unset",shell->list->command[0]) == 0 )
		ft_unset(shell);
	else if (ft_strcmp("exit",shell->list->command[0]) == 0)
		ft_exit(shell);
	else 
		ft_exec_non_builtin(shell , flag);
}

void ft_execut_simple_command(t_shell *shell )
{
	int original_stdin;
	int original_stdout;

	original_stdin = dup(0);
	original_stdout = dup(1);
	if(shell->list->fd_input != -1)
	{
		dup2(shell->list->fd_input,0);
		close(shell->list->fd_input);
	}
	if(shell->list->fd_output != -1)
	{
		dup2(shell->list->fd_output , 1);
		close(shell->list->fd_output);
	}
	execute_command(shell , 0);
	dup2(original_stdin, 0);
	dup2(original_stdout, 1);
	close(original_stdin);
	close(original_stdout);
}


void ft_execution(t_shell *shell)
{

	int i = 0;
	shell->list->fd_heredoc = -1;
	shell->list->fd_input = -1;
	shell->list->fd_output = -1;
	// handle_heredoc(shell);
	i = ft_open_redictions(shell);
	if(i < 0)
		return;
	if(ft_cmnd_nb(shell->list) == 1)
	{	
		ft_execut_simple_command(shell);
		return;
	}
int preve_fd = -1;
int nb = ft_cmnd_nb(shell->list);
int fd[2] = {-1, -1};
int id = -1;
int child_pids[nb];
 i = 0;
	while (shell->list != NULL) 
	{
		shell->list->fd_heredoc = -1;
		shell->list->fd_input = -1;
		shell->list->fd_output = -1;
		if (ft_open_redictions(shell) == -1) 
		{
        	printf("Error opening redirection files\n");
		}
		pipe(fd); 
    	id = fork();

    	if (id == 0) 
		{ 
        	if (i == 0) 
			{
            	dup2(fd[1], 1); 
        	} 
			else if(i < nb - 1) 
			{
            	dup2(preve_fd, 0);  
            	dup2(fd[1], 1);
       		} 
			else 
			{
            	dup2(preve_fd, 0);
     		}
			if(shell->list->fd_input != -1)
			{
				dup2(shell->list->fd_input,0);
				close(shell->list->fd_input);
			}
			if(shell->list->fd_output != -1)
			{
				dup2(shell->list->fd_output , 1);
				close(shell->list->fd_output);
			}
			close(shell->list->fd_input);
			close(shell->list->fd_output);
        	close(fd[0]);
        	close(fd[1]);
        	if (preve_fd != -1)
	   			close(preve_fd);

       		execute_command(shell ,1);
        	exit(shell->exit_status);
		} 
		else 
		{ 
		
			child_pids[i] = id;
        	if (preve_fd != -1) 
				close(preve_fd);
        	preve_fd = fd[0];
        	close(fd[1]);
            if (shell->list->fd_input != -1) 
				close(shell->list->fd_input);
            if (shell->list->fd_output != -1) 
				close(shell->list->fd_output);
        	 
        	shell->list = shell->list->next;
        	i++;
    	}
}

if(preve_fd != -1)
	close(preve_fd);
int status = 0;
int signal_nb = 0;
for (int j = 0; j < nb; j++) 
{
	if(j == nb - 1)
	{
		waitpid(child_pids[j],&status,0);
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
    waitpid(child_pids[j], NULL, 0);
}
}


