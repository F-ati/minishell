/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-02 08:33:00 by root              #+#    #+#             */
/*   Updated: 2024-11-02 08:33:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
// #include <type.h>

int main()
{
    int pid = fork();
    int status = 0;
    int exit_status ;
    int signal_nb;
    if (pid == 0)
    {
        printf("pid [%d]\n",getpid());
        sleep(20); 
        exit(42);
    }
    else
    {
        waitpid(pid,&status,0);
        if(WIFEXITED(status) == true)
        {
            exit_status = WEXITSTATUS(status);
            printf("=====>exit_status %d\n",exit_status);
        }
        if(WIFSIGNALED(status) == true)
        {
            signal_nb =  WTERMSIG(status) ;
            exit_status = 128 + signal_nb;
            printf("====>signal_nb %d\n====>exit_status %d\n",signal_nb,exit_status);
        }
    }
}