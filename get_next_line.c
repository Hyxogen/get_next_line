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
#include <limits.h>

static int is_valid_fd(int fd) {
	if ((fd >= 0) && (fd <= OPEN_MAX))
		return (TRUE);
	return (FALSE);
}

static char *process_line(char *line, char *line_end, char *remaining, size_t len) {
	char *ret;
	size_t line_len;

	if (!len) {
		free(line);
		return (NULL);
	}
	line_len = line_end - line + 1;
	ret = ft_strndup(line, line_len);
	if (!ret) {
		free(line);
		return (NULL);
	}
	printf("Len: %zu, line_len %zu Copying %zu bytes!\n", len, line_len, len - (line_len + 1));
	ft_memcpy(remaining, line + line_len, len - line_len);
	free(line);
	return (ret);
}

char *get_next_line(int fd) {
	static char buffer[BUFFER_SIZE];
	char *ret;
	char *line_end;
	char *realloc_temp;
	size_t bytes_read_total;
	ssize_t bytes_read;

	if (!is_valid_fd(fd))
		return (NULL);
	ret = malloc(BUFFER_SIZE);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, &buffer[0], BUFFER_SIZE);
	line_end = NULL;
	bytes_read_total = 0;
	bytes_read = 1;
	while (1) {
		line_end = ft_memchr(ret, '\n', bytes_read_total);
		if (line_end || !bytes_read)
			return process_line(ret, line_end, &buffer[0], bytes_read_total);
		bytes_read = read(fd, &buffer[0], BUFFER_SIZE);
		if (bytes_read < 0) {
			free(ret);
			return (NULL);
		}
		realloc_temp = ft_realloc(ret, bytes_read_total, bytes_read_total + bytes_read);
		if (!realloc_temp) {
			free(ret);
			return (NULL);
		}
		ret = realloc_temp;
		ft_memcpy(ret + bytes_read_total, &buffer[0], bytes_read);
		bytes_read_total += bytes_read;
	}
}