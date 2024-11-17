// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   save.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/11/16 12:28:41 by fel-aziz          #+#    #+#             */
// /*   Updated: 2024/11/16 12:28:41 by fel-aziz         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// if(str[0] == '$')
// 		{
// 			char *varName = ft_strdup(&str[1]);
// 			indix = ft_is_env_var(shell, varName);
// 			if(indix >= 0)
// 			{
// 				len = ft_strlen(varName) + 1;
// 				while(shell->env[indix][len] != '\0')
// 				{
// 					write (fd,&shell->env[indix][len],1);
// 					len++;
// 				}
// 			}
// 			write(fd,"\n",1);
// 		}
// 		else
// 		{
// 			len = ft_strlen(str);
// 			i = 0;
// 			while(i < len)
// 			{
// 				write (fd,&str[i],1);
// 				i++;
// 			}
// 			write(fd,"\n",1);
// 		}

// int	ft_is_env_var(t_shell *shell, char *str)
// {
// 	int	len;
// 	int	i;

// 	i = 0;
// 	len = ft_strlen(str);
// 	while (shell->env[i] != NULL)
// 	{
// 		if (strncmp(shell->env[i], str, len) == 0 && shell->env[i][len] == '=')
// 			return (i);
// 		i++;
// 	}
// 	return (-7);
// }