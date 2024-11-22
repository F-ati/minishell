/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:08:34 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/11/22 15:48:41 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_is_exist(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_free_env(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

int	ft_cmnd_nb(t_list *data)
{
	t_list	*tmp;
	int		i;

	tmp = data;
	i = 0;
	if (data == NULL)
	{
		return (0);
	}
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_herdoc_nb(t_list *save)
{
	int		i;
	t_dir	*redir_cur;
	t_list	*cur;

	i = 0;
	cur = save;
	if (save == NULL)
		return (0);
	while (cur != NULL)
	{
		redir_cur = cur->redir;
		while (redir_cur != NULL)
		{
			if (redir_cur->type == HEREDOC)
			{
				i++;
			}
			redir_cur = redir_cur->next;
		}
		cur = cur->next;
	}
	return (i);
}

int	ft_strnb(char **str)
{
	int	j;

	j = 0;
	while (str[j] != NULL)
	{
		j++;
	}
	return (j);
}

int	get_var_indix(char **exp_or_env, char *name_var)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(name_var);
	while (exp_or_env[j] != NULL)
	{
		if ((exp_or_env[j][0] == name_var[0] && strncmp(exp_or_env[j], name_var,
					len) == 0) && (exp_or_env[j][len] == '='
				|| exp_or_env[j][len] == '\0'))
		{
			return (j);
		}
		j++;
	}
	return (-7);
}

int	ft_check_is_number(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	if ((str[i] == '-' || str[i] == '+') && (str[i + 1] != '\0'))
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		i++;
	if (i == len)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	cmmnd_len(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	check_invalid_arg(char *command)
{
	int	i;

	if ((command[0] >= 'a' && command[0] <= 'z') || (command[0] >= 'A'
			&& command[0] <= 'Z') || (command[0] == '_'))
	{
		i = 1;
		while (command[i] != '\0' && command[i] != '=')
		{
			if ((command[i] < 'a' || command[i] > 'z') && (command[i] < 'A'
					|| command[i] > 'Z') && (command[i] < 48 || command[i] > 57)
				&& (command[i] != '_'))
			{
				return (-7);
			}
			i++;
		}
	}
	else
	{
		return (-7);
	}
	return (1);
}

char	*my_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		result[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	free(s1);
	return (result);
}

void	ft_free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		free(path[i]);
		i++;
	}
}

int	ft_write_data(int fd, char *value)
{
	int	i;

	i = 0;
	if (value == NULL)
		return (i);
	while (value[i] != '\0')
	{
		write(fd, &value[i], 1);
		i++;
	}
	return (i);
}

void	update_exit_status_env(t_shell *shell)
{
	char	*tmp[2];

	tmp[1] = ft_itoa(shell->exit_status);
	tmp[0] = ft_strjoin("?=", tmp[1]);
	ft_apdate_env(shell, tmp[0]);
	free(tmp[0]);
	free(tmp[1]);
}

char	*generate_temp_filename(char *file_name)
{
	file_name = ft_strjoin("/tmp/.", file_name);
	while (access(file_name, F_OK) == 0)
	{
		file_name = my_strjoin(file_name, "1");
	}
	return (file_name);
}

int	display_variable(t_shell *shell, char *str, int i, int fd)
{
	char	*valid_var;
	char	*value;
	int		len;

	len = 0;
	valid_var = get_variable(str, i + 1);
	len = ft_strlen(get_variable(str, i + 1));
	value = get_env_value(shell->env, valid_var);
	free(valid_var);
	ft_write_data(fd, value);
	return (len);
}

int	ft_handle_input_redirection(t_shell *shell, t_dir *redir)
{
	if (redir->type == HEREDOC)
	{
		close(shell->list->fd_input);
		shell->list->fd_input = open(redir->herdoc_file_name, O_RDWR, 0777);
		if (shell->list->fd_input == -1)
			return (-1);
	}
	else if (redir->type == IN)
	{
		close(shell->list->fd_input);
		shell->list->fd_input = ft_open_input(redir->file_name, shell);
		if (shell->list->fd_input == -1)
			return (-1);
	}
	return (1);
}

int	ft_handle_output_redirection(t_shell *shell, t_dir *redir)
{
	if (redir->type == OUT)
	{
		close(shell->list->fd_output);
		shell->list->fd_output = ft_open_output(redir->file_name, shell);
		if (shell->list->fd_output == -1)
			return (-1);
	}
	else if (redir->type == APPEND)
	{
		close(shell->list->fd_output);
		shell->list->fd_output = ft_open_append(redir->file_name, shell);
		if (shell->list->fd_output == -1)
			return (-1);
	}
	return(1);
}

void print_error(t_shell  *shell,char *old_pwd)
{
		free(old_pwd);
		perror("minishell: cd");
		shell->exit_status = 1;
}

char *go_to_home(t_shell *shell)
{
	char *path;
	path = get_env_value(shell->env, "HOME");
	if (path == NULL)
	{
		ft_printf("minishell: cd: HOME not set\n");
		shell->exit_status = 1;
		return(NULL);
		
	}
	return(path);
}
void ensure_fds_closed(t_list *list)
{
	t_list *tmp;

	tmp = list ;
	while(tmp != NULL)
	{
		if(tmp->fd_heredoc >= 0)
		{
			close(tmp->fd_heredoc);
			tmp->fd_heredoc = -1;
		}
		if(tmp->fd_input >= 0)
		{
			close(tmp->fd_input);
			tmp->fd_input = -1;
		}
		if(tmp->fd_output >= 0)
		{
			close(tmp->fd_output);
			tmp->fd_output = -1;
		}
		tmp = tmp->next;
	}
}

void	ft_set_pwd_env(t_shell *shell, char *pwd, int j)
{
	free(shell->env[j]);
	shell->env[j] = ft_strjoin("PWD=", pwd);
}

void	export_invalid_arg_error(t_shell *shell, char *str)
{
	ft_printf("minishell: export: '%s': not a valid identifier\n", str);
	shell->exit_status = 1;
}

void	check_export_cases(char c, int *flag)
{
	if (c == '\"' || c == '$')
		write(1, "\\", 1);
	write(1, &c, 1);
	if (c == '=' && *flag == 0)
	{
		write(1, "\"", 1);
		*flag = 1;
	}
}
char	**remove_and_resize(char **str, int indx)
{
	char	**p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	p = malloc(sizeof(char *) * ft_strnb(str));
	if (p == NULL)
		return (NULL);
	while (str[i] != NULL)
	{
		if (i == indx)
			free(str[i++]);
		else
			p[j++] = str[i++];
	}
	p[j] = NULL;
	free(str);
	return (p);
}