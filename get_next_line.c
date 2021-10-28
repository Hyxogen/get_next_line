/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/27 09:32:30 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/10/27 17:31:49 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <stdio.h>


static char
    *get_line_end(char *str, size_t len)
{
    char    *ret;

    ret = ft_memchr(str, '\n', len);
    if (!ret)
        ret = ft_memchr(str, '\0', len);
    return (ret);
}

/*
 * Probably a good idea to zero the remaining afterwards
 */
static char
    *process_line(char *str, char *remaining, char *line_end, size_t len)
{
   char     *ret;
   size_t   line_len;

   printf("Line start:%lx line end:%lx line len:%zu\n", (unsigned long) str, (unsigned long) line_end, len);
   line_len = line_end - str + 1;
   printf("Line len:%zu\n", line_len);
   ret = ft_strndup(str, line_len);
   if (!ret)
       return (NULL);
   len -= line_len;
   line_end++;
   printf("Going to copy %zu bytes\n", len);
   //Het gaat 'fout' bij memcpy
   ft_memcpy(remaining, line_end, len);
   ft_memset(remaining + len, 0, BUFFER_SIZE - len); //This is probably not right
   printf("Remaining:\"%s\"\n", remaining);
   return (ret);
}

int i = 0;

/*
 * TODO Remove lin_end != ret by checking if the number of bytes read < BUFFER_SIZE
 */
char
    *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    char        *ret;
    char        *temp;
    char        *line_end;
    ssize_t     bytes_read_total;
    ssize_t     bytes_read;

    if (fd < 0)
        return (NULL);
    ret = malloc(BUFFER_SIZE);
    if (!ret)
        return (NULL);
    ft_memcpy(ret, &buffer[0], BUFFER_SIZE);
    bytes_read = BUFFER_SIZE;
    bytes_read_total = 0;
    printf("Before while loop\n");
    while (1)
    {
        printf("Top while loop, ret:\"%s\"\n", ret);
        line_end = ft_memchr(ret, '\n', bytes_read_total);
        printf("Line end:%lx\n", (unsigned long) line_end);
        if (line_end || bytes_read < BUFFER_SIZE)
        {
            printf("Found a line\n");
            temp = process_line(ret, &buffer[0], line_end, bytes_read_total);
            if (!temp)
                free(ret);
            return (temp);
        }
        bytes_read = read(fd, &buffer[0], BUFFER_SIZE);
        printf("Read %ld bytes\n", bytes_read);
        if (bytes_read <= 0)
        {
            free(ret);
            return (NULL);
        }
        printf("Start realloc\n");
        ret = ft_realloc(ret, bytes_read_total, bytes_read_total + bytes_read);
        printf("Realloced\n");
        if (!ret)
        {
            free(ret);
            return (NULL);
        }
        printf("Start memcpy, before:\"%s\"\n", ret);
        ft_memcpy(ret + bytes_read_total, &buffer[0], bytes_read);
        bytes_read_total += bytes_read;
        printf("Total bytes read: %ld after:\"%s\"\n", bytes_read_total, ret);
        if (i == 12)
            break;
        i++;
    }
    return (NULL);
}
