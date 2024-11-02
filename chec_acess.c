/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chec_acess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-31 13:04:34 by root              #+#    #+#             */
/*   Updated: 2024-10-31 13:04:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    int i ;
    i = access("sd,n", W_OK | X_OK | R_OK);
    if ( i == 0)
    {
        printf("looool all is good \n");
    }
    else if (i == -1)
    {
        perror("bash : ");
    }
}