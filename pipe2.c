/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:38:22 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/09/03 15:35:42 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define NUM_COMMANDS 6

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    int pipefd[2];
    int prev_pipefd[2] = {-1, -1};
    pid_t pids[NUM_COMMANDS];
    int i;
    char *commands[NUM_COMMANDS][4] = {
        {"/usr/bin/env", NULL},
        {"/usr/bin/grep", "HOME", NULL},
        {"/usr/bin/sort", NULL},
        {"/usr/bin/wc", "-l", NULL},
        {"/usr/bin/head", "-n", "5", NULL},
        {"/usr/bin/tail", "-n", "3", NULL}
    };

    i = 0;
    while (i < NUM_COMMANDS)
    {
        if (i < NUM_COMMANDS - 1)
        {
            pipe(pipefd);
        }
        pids[i] = fork();
        if (pids[i] == 0)
        {
            if (i > 0)
            {
                dup2(prev_pipefd[0], 0);
                close(prev_pipefd[0]);
                close(prev_pipefd[1]);
            }
            if (i < NUM_COMMANDS - 1)
            {
                dup2(pipefd[1], 1);
                close(pipefd[0]);
                close(pipefd[1]); 
            }
            execve(commands[i][0], commands[i], env);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        if (i > 0)
        {
            close(prev_pipefd[0]);
            close(prev_pipefd[1]);
        }
        if (i < NUM_COMMANDS - 1)
        {
            prev_pipefd[0] = pipefd[0];
            prev_pipefd[1] = pipefd[1];
        }
        ++i;
    }
    if (prev_pipefd[0] != -1)
    {
        close(prev_pipefd[0]);
        close(prev_pipefd[1]);
    }
    for (i = 0; i < NUM_COMMANDS; ++i)
    {
        waitpid(pids[i], NULL, 0);
    }
    return 0;
}
