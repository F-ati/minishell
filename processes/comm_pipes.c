/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:11:57 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/08/23 12:11:08 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

// int main()
// {
// 	int fd[2];
// 	pipe(fd);
// 	int id = fork();
// 	if (id == -1 )
// 	{
// 		printf ( "error in fork\n");
// 		return (2);
// 	}
	
// 	if ( id == 0)
// 	{
// 		close(fd[0]);
		
// 		int y ;
// 		printf("enter the number :  \n");
// 		scanf("%d", &y);
// 		write(fd[1], &y, sizeof(int ));
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		int buf = 0;
// 		read(fd[0],&buf, sizeof(int));
// 		printf("got from child p %d\n",buf);
// 		close(fd[0]);
// 	}
	
// 	wait(NULL);
// }


// int main()
// {
// 	int arr[] = { 1, 2 ,10, 4, 5,6};
// 	int fd[2];
// 	pipe(fd);
// 	int id = fork();
// 	if (id == 0)
// 	{
// 		int r = 0;
// 		int i = 0;
// 		int size = sizeof(arr) / sizeof(arr[1]);
// 		while ( i < size / 2)
// 		{
// 			r += arr[i];
// 			i ++;
// 		}
// 		write(fd[1], &i, sizeof(int));
// 		// write(fd[1],&i,sizeof(int));

// 	}
// 	else
// 	{
// 		int buf;
// 		read(fd[0],&buf,sizeof(int));
		 
// 		printf("%d\n",buf);
// 	}
// 	wait(NULL);
// 	return(0);
// }

int main()
{
	int fd[2];
	int id;
	int i = 0;
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		close (fd[0]);
		char str[] = "fatima";
		while (str[i] != '\0')
		{
			write(fd[1],&str[i],1);
			i++;
		}
		close (fd[1]);

	}
	else
	{
		wait(NULL);
		close (fd[1]);
		char x[9];
		int i ;
		i = read(fd[0] , &x, sizeof(char) * 7 );
		x[i] = '\0';
		printf("%s\n", x);
		close(fd[0]); 
	}

	
}