/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/27 09:32:30 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/11/01 12:24:07 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <stdio.h>

/*
 * Probably a good idea to zero the remaining afterwards
 */
static char
    *process_line(char *str, char *remaining, char *line_end, size_t len)
{
   char     *ret;
   size_t   line_len;

	if (!line_end)
	{
		ft_memset(remaining, 0, BUFFER_SIZE);
		return (NULL);
	}
	line_len = line_end - str + 1;
	ret = ft_strndup(str, line_len);
	if (!ret) {
	   return (NULL);
   }
   len -= line_len;
   line_end++;
   //Het gaat 'fout' bij memcpy
   ft_memcpy(remaining, line_end, len);
   ft_memset(remaining + len, 0, BUFFER_SIZE - len); //This is probably not right
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

//    ret = malloc(5);
    if (fd < 0)
        return (NULL);
    ret = malloc(BUFFER_SIZE);
    if (!ret)
        return (NULL);
    ft_memcpy(ret, &buffer[0], BUFFER_SIZE);
    bytes_read = BUFFER_SIZE;
    temp = ft_memchr(&buffer[0], '\0', BUFFER_SIZE - 1);
    bytes_read_total = 0;
    if (temp)
    	bytes_read_total = temp - &buffer[0];
    line_end = NULL;
    while (1)
    {
    	if (bytes_read_total)
        	line_end = ft_memchr(ret, '\n', bytes_read_total - 1);
        if (line_end || bytes_read < BUFFER_SIZE)
        {
            temp = process_line(ret, &buffer[0], line_end, bytes_read_total);
            free(ret);
            return (temp);
        }
        bytes_read = read(fd, &buffer[0], BUFFER_SIZE);
        if (bytes_read < 0 || (bytes_read == 0 && !buffer[0]))
        {
            free(ret);
            return (NULL);
        }
        temp = ft_realloc(ret, bytes_read_total, bytes_read_total + bytes_read);
        if (!temp)
        {
            free(ret);
            return (NULL);
        }
        ret = temp;
        ft_memcpy(ret + bytes_read_total, &buffer[0], bytes_read);
        bytes_read_total += bytes_read;
        if (i == 12)
            break;
        i++;
    }
    return (NULL);
}
