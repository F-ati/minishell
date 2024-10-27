/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:30:28 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/08/19 10:10:14 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

int main()
{
  int id1 =  fork();
  int id2 = fork();
  if ( id1 == 0 )
  {
    if ( id2 == 0)
    {
      printf("hafid \n");
    }
    else 
    {
      printf("walid \n");

    }
  }

    else
    {
      if (id2 == 0)
      {
        printf("walid 2\n");
      }
      else
      {
        printf("helllo\n");
      }
    }
    while( wait(NULL) != -1 && errno != ECHILD)
      printf(" stina \n");
    return (0);
  }
