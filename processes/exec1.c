/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-30 19:03:49 by root              #+#    #+#             */
/*   Updated: 2024-10-30 19:03:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("PID of the exec1.c %d \n", getpid());
    char *str[] = {"hello","fatima","elazizi",NULL};
    execv("exec2",str);
    printf("bach to ex1");
    return(0);
}