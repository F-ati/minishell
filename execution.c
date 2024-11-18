/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:58:09 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/18 21:52:15 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_execve(t_shell *shell,char *path)
{
	int pid;
	int status;
	int signal_nb;
	pid = fork();
	if(pid == 0)
	{
		execve(path, shell->list->command, shell->env);
		perror("bash : execve");
		shell->exit_status = 1;
		exit(shell->exit_status);
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
		ft_printf("minishell: %s: No such file or directory\n",shell->list->command[0]);
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
			ft_printf("minishell: %s : No such file or directory\n",shell->list->command[0]);
			shell->exit_status = 127;
		}
		else if (path[i] == NULL)
		{
			ft_printf("minishell: %s: command not found\n" ,shell->list->command[0]);
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
		ft_cd(shell);
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
		// dprintf(shell->list->fd_input, "lslslslsls==>%d\n",shell->list->fd_input);
		dup2(shell->list->fd_input, 0);
		close(shell->list->fd_input);
	}
	if(shell->list->fd_output != -1)
	{
		dup2(shell->list->fd_output, 1);
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
	char *tmp[2];
	shell->list->fd_heredoc = -1;
	shell->list->fd_input = -1;
	shell->list->fd_output = -1;
	handle_heredoc(shell);
	i = ft_open_redictions(shell);
	if(i < 0)
	{
		return;
	}
	// printf("==>%d\n",shell->list->fd_input);
	if(ft_cmnd_nb(shell->list) == 1)
	{	
		ft_execut_simple_command(shell);
		tmp[1] = ft_itoa(shell->exit_status);
		tmp[0] = ft_strjoin("?=", tmp[1]);
		ft_apdate_env(shell ,tmp[0]);
		free (tmp[0]);
		free (tmp[1]);
		return;
	}
int preve_fd = -1;
int nb = ft_cmnd_nb(shell->list);
int fd[2] = {-1, -1};
int id = -1;
int child_pids[nb];
 i = 0;
	while (shell->list != NULL ) 
	{
		shell->list->fd_heredoc = -1;
		shell->list->fd_input = -1;
		shell->list->fd_output = -1;
		if (ft_open_redictions(shell) == -1) 
		{
			return;
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
int j = 0;
while( j < nb) 
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
	j++;
}
t_list	*save_list;
t_dir	*save_redir;

save_list = NULL;
save_redir = NULL;
save_list = shell->list;
while (save_list != NULL)
{
	save_redir = save_list->redir;
	while (save_redir != NULL)
	{
		// unlink(save_redir->herdoc_file_name);
		free(save_redir->herdoc_file_name);
		save_redir = save_redir->next;
	}
	save_list = save_list->next;
}

}


