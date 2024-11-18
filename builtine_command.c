/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtine_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:16:27 by root              #+#    #+#             */
/*   Updated: 2024/11/18 12:51:26 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// echo command 

void ft_print_str(t_shell *minishell , int flag)
{
	int i ;
	int j = flag;
		
	while (minishell->list->command[j] != NULL)
	{
		i = 0;
		while (minishell->list->command[j][i] != '\0')
		{
			
			write (1, &minishell->list->command[j][i], 1);
			i++;
		}
		if(minishell->list->command[j + 1] != NULL)
			write (1, " ", 1);
		j++;
	}
	if (flag == 1)
		write (1, "\n", 1);
	
}

void ft_echo(t_shell *shell)
{
	
	int i;
	int j ;
	j = 1;
	i = 0;
	while(shell->list->command[j] != NULL && shell->list->command[j][i] == '-')
	{
		i++;
		while(shell->list->command[j][i] != '\0' && shell->list->command[j][i] == 'n')
		{
			i++;
		}
		if(shell->list->command[j][i] == '\0')
		{
			j++;
			i = 0;
		}
		else
		{
			break;
		}
	}
	ft_print_str(shell,j);
	shell->exit_status = 0;
}

//  env command 

void  ft_env(t_shell *data)
{
	int j = 0;
	int i ;
	while (data->env[j] != NULL)
	{
		i = 0;
		while (data->env[j][i] != '\0' && data->env[j][0] != '$')
		{
			write(1,&data->env[j][i],1);
			i ++;
		}
		if(data->env[j][0] != '$')
			write(1,"\n",1);
		j ++;
	}
	data->exit_status = 0;
}

// pwd command ;
void ft_pwd(t_shell *shell)
{
	char *path;
    path = getcwd(NULL,0);
    if(path == NULL)
    {
        perror("bash: pwd: getcwd");
        // exit(1);
		shell->exit_status = 1;
		return;
    }
    printf("%s\n",path);
	shell->exit_status = 0;
    free(path);
}


// cd command 

void update_pwd_env(t_shell *shell ,char *old_pwd)
{
	int j = 0;
	char *save_for_free ;
	char *PWD = getcwd(NULL,0);
    if (PWD ==  NULL)
    {
        perror("bash: cd");
		shell->exit_status = 1;
		
    }
	while(shell->env[j] != NULL)
	{
		if(shell->env[j][0] == 'P' && strncmp(shell->env[j] ,"PWD",3) == 0 && shell->env[j][3] == '=')
		{
			save_for_free = shell->env[j];
			shell->env[j] = ft_strjoin("PWD=",PWD);
			free(save_for_free);
		}	
		if (shell->env[j][0] == 'O' && strncmp(shell->env[j] ,"OLDPWD",6) == 0 && shell->env[j][6] == '=')
		{
			save_for_free = shell->env[j];
			shell->env[j] = ft_strjoin("OLDPWD=",old_pwd);
			free(save_for_free);
		}
		j++;
	}
	free(old_pwd);
	free(PWD);
}

void ft_cd(t_shell *shell)
{
    char *path;
	int args_nb = cmmnd_len(shell->list->command);

    if ( args_nb == 1) // shell->list->commnd[1] == NULL;
    {
        path = get_env_value(shell->env , "HOME");
        if(path == NULL)
        {
            printf("minishell: cd: HOME not set\n");
            shell->exit_status = 1;
            return;
        }
    }
    else
	{
		path = shell->list->command[1]; 
	}
	char *old_pwd = getcwd(NULL,0);
    if (old_pwd ==  NULL)
    {
        perror("bash: cd");
        shell->exit_status = 1;
		return;
    }
	if (chdir(path) < 0) 
	{
		// printf("====>%s\n",path);
    	perror("loool bash: cd");
        shell->exit_status = 1;
        return;
    }
	shell->exit_status = 0;
    update_pwd_env(shell,old_pwd);
}
//  export command ;

int check_is_has_value(char *command)
{
	int i = 0;
	while(command[i] != '\0')
    {
		if(command[i] == '=')
		{
			return (1);
		}
		i++;
	}
	return(0);
}
 
char **ft_resize(char **str, char *new_var)
{
	char **p;
	int len ;
	len = ft_strnb(str);
	p =  ft_calloc(sizeof(char *), (len + 2));
	if (p == NULL)
		return(NULL);
	len = 0;
	while(str[len] != NULL)
	{
		p[len] = str[len];
		len++;
	}
	p[len] = ft_strdup(new_var);
	len++;
	// printf("%s\n",p[len - 1]);
	return(p);
}

char *get_name_var(char *command)
{
	char *p;
	int i = 0;
	while (command[i] != '='  && command[i] != '\0')
	{
		i++;
	}
	p = malloc(sizeof(char) * ( i + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while(command[i] != '=' && command[i] != '\0')
	{
		p[i] = command[i];
		i++;
	}
	p[i] = '\0';
	return(p);
}

void ft_apdute_env(t_shell *shell,char *new_arg)
{
    int indix ;
	char *var_name = get_name_var(new_arg);
	indix = get_var_indix(shell->env ,var_name);
	if(indix < 0)
	{
		shell->env = ft_resize(shell->env,new_arg);
	}
	else
	{
		shell->env[indix] = ft_strdup(new_arg);
	}
	free(var_name);
}


void  ft_apdute_export(t_shell *shell , char *new_arg)
{
	int indix ;
	char *for_free;
	char *var_name = get_name_var(new_arg);
	indix = get_var_indix(shell->export ,var_name);
	if(indix < 0)
	{
		shell->export = ft_resize(shell->export,new_arg);
	}
	else
	{
		for_free = shell->export[indix];
		shell->export[indix] = ft_strdup(new_arg);
		free(for_free);
	}
	free(var_name);
}

void ft_export(t_shell *shell , int flag)
{
	int i = 0;
	(void)flag;
	if (shell->list->command[1] == NULL)
	{
		while (shell->export[i] != NULL)
		{
			printf("declare -x %s\n",shell->export[i]);
			i++;
		}
		shell->exit_status = 0;
		return;
	} 
	i = 1;
	while(shell->list->command[i] != NULL)
	{
		if(check_invalid_arg(shell->list->command[i]) == 1)
		{
			if(check_is_has_value(shell->list->command[i]) == 1)
			{
				
				ft_apdute_env(shell , shell->list->command[i]);	
			}
			ft_apdute_export(shell,shell->list->command[i]);
			shell->exit_status = 0;
		}
		else
		{
			printf("bash: export: '%s': not a valid identifier\n",shell->list->command[i]);
			shell->exit_status = 1;
		}
		i++;
	}	
}

// unset func 

char  **remove_and_resize(char **str,int indx)
{
    int len;
    char **p;
    int i = 0;
    int j = 0;
    len =  ft_strnb(str);
    p = malloc (sizeof(char *) * len );
    if(p == NULL)
    {
        return(NULL);

    }
	while (str[i] != NULL)
	{
		if ( i == indx)
		{
            // free(str[i]);
			i++;
		}
		else
		{
		  p[j] = str[i];
			j++;
		    i++;
		}
		
	}
    
	p[j] = NULL;
	return(p);
}
    
void  ft_unset(t_shell *shell)
{
    int indx1;
    int indx2;
    int i =  1;
    while(shell->list->command[i] != NULL)
    {
		if(check_invalid_arg(shell->list->command[i]) == 1)
		{
			indx1 = get_var_indix(shell->export,shell->list->command[i]);
			indx2 = get_var_indix(shell->env,shell->list->command[i]);
			if(indx1 >= 0 )
			{
				// free old export;
				shell->export = remove_and_resize(shell->export,indx1);
			}
			if (indx2 >= 0)
			{
				// free old env;
				shell->env = remove_and_resize(shell->env,indx2);
			}
			shell->exit_status = 0;
		}
		else
		{
			printf("bash: unset: %s: not a valid identifier\n",shell->list->command[i]);
			shell->exit_status = 1;
		}
		i++;
    }
    ft_export(shell,0);
}

// exit func

void  ft_exit(t_shell *shell)
{
	int nb ;
	int len = cmmnd_len(shell->list->command);
	if(len == 1)
	{
		shell->exit_status = 0;
		exit(0);
	}
	if ( len == 2 && ft_check_is_number(shell->list->command[1]) == 1)
	{
		nb = ft_atoi(shell->list->command[1]);
		if(nb > 255  )
		{
			nb = nb % 256;
		} 
		shell->exit_status = nb;
		printf("exit\n");
		exit(nb);
	}
	if ( ft_check_is_number(shell->list->command[1]) == 0)
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n",shell->list->command[1]);
		shell->exit_status = 255 ;
		exit(255);
		
	}
	if ( ft_check_is_number(shell->list->command[1]) == 1 && len > 2)
	{
		shell->exit_status = 1;
		printf("exit\nbash: exit: too many arguments\n");
	}
}