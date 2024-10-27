/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:57:03 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/08/27 13:11:07 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int ac, char **av, char **env)
{
    (void)av;
    (void)ac;

    int pipefd[2], fd[2];
    pid_t pid1, pid2, pid3;

    char *args1[] = {"/usr/bin/env", NULL};
    char *args2[] = {"/usr/bin/grep", "HOME", NULL};
    char *args3[] = {"/usr/bin/sort", NULL};

    pipe(pipefd);
    pipe(fd);
    pid1 = fork();
    if (pid1 == 0)
    {
        dup2(pipefd[1], 1);
        close(pipefd[0]);
        close(pipefd[1]);
        close(fd[1]);        
        close(fd[0]);
        execve(args1[0], args1, env);
        perror("execve");
        exit(EXIT_FAILURE);
    } 
    pid2 = fork();
    if (pid2 == 0)
    {
        dup2 (fd[1], 1);
        dup2 (pipefd[0], 0);
        close(pipefd[0]);
        close(pipefd[1]);
        close(fd[1]);
        close(fd[0]);
        execve(args2[0], args2, env);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    pid3 = fork();
    if (pid3 == 0)
    {
        dup2(fd[0], 0);

        close(pipefd[0]);
        close(pipefd[1]);
        close(fd[1]);        
        close(fd[0]);
        execve (args3[0], args3, env);
        exit (1);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    return 0;
}