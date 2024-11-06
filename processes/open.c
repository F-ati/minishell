/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-06 07:38:12 by root              #+#    #+#             */
/*   Updated: 2024-11-06 07:38:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // For open flags
#include <unistd.h>     // For close, read, write, lseek
#include <string.h>
#include <errno.h>

#define FILENAME "example.txt"
#define BUFFER_SIZE 1024

int main() {
    int fd;
    fd = open(FILENAME, O_RDWR | O_CREAT);
    if (fd == -1) 
    {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd,1) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    printf("hello word\n");
    if (close(fd) == -1)
    {
        perror("Error closing the file");
        exit(EXIT_FAILURE);
    }

    return 0;
}
