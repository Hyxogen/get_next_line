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

//Always returns a NULL pointer
//static char *CleanUp(char *ret, t_line_buffer *line_buffer) {
//	free(ret);
//	line_buffer->m_BufferSize = 0;
//	line_buffer->m_Start = NULL;
//	ft_memset(&line_buffer->m_Buffer[0], 0, BUFFER_SIZE); //TODO check if needed
//	return (NULL);
//}

/**
 *
 * @param fd a valid file descriptor
 * @return the t_line_buffer corresponding to the file descriptor
 */
static t_line_buffer *GetLineBuffer(int fd) {
	static t_line_buffer line_buffers[OPEN_MAX];
	t_line_buffer *ret;

	ret = &line_buffers[fd];
	ret->m_End = &(ret->m_Buffer[BUFFER_SIZE - 1]);
	if (!ret->m_Start)
		ret->m_Start = &ret->m_Buffer[0];
	return (&line_buffers[fd]);
}
//Alloc size van size 0 zorgt voor problemen
static char *ProcessLine(char *tmp, size_t tmp_size, t_line_buffer *line_buffer, char *line_end) {
	char *ret;
	size_t copy_len;

	copy_len = line_end - line_buffer->m_Start + 1;
	ret = ft_realloc(tmp, tmp_size, tmp_size + copy_len + 1);
	if (!ret) {
		free(tmp);
		return (NULL);
	}
	ft_memcpy(ret + tmp_size, line_buffer->m_Start, copy_len);
	ret[tmp_size + copy_len] = 0;
	line_buffer->m_Start = line_end + 1;
	line_buffer->m_BufferSize -= copy_len;
	return (ret);
}

char *get_next_line(int fd) {
	t_line_buffer *lineBuffer;
	char *tmp;
	char *line_end;
	ssize_t bytes_read;
	size_t tmp_len;

	if (!((fd >= 0) && (fd <= OPEN_MAX)))
		return (NULL);
	lineBuffer = GetLineBuffer(fd);
	bytes_read = 1;
	tmp_len = 0;
	tmp = NULL;
	while (1) {
		line_end = ft_memchr(lineBuffer->m_Start, '\n', lineBuffer->m_BufferSize);
		if (line_end || !bytes_read)
			return (ProcessLine(tmp, tmp_len, lineBuffer, line_end));
		line_end = ft_realloc(tmp, tmp_len, tmp_len + lineBuffer->m_BufferSize);
		if (!line_end) {
			free(tmp);
			return (NULL);
		}
		tmp = line_end;
		tmp_len += lineBuffer->m_BufferSize;
		lineBuffer->m_BufferSize = BUFFER_SIZE;
		lineBuffer->m_Start = &lineBuffer->m_Buffer[0];
		bytes_read = read(fd, lineBuffer->m_Start, BUFFER_SIZE);
		if (bytes_read < 0) {
			free(tmp);
			return (NULL);
		}
	}
}

//char *get_next_line(int fd) {
//	t_line_buffer *line_buffer;
//	char *ret;
//	char *line_end;
//	char *realloc_temp;
//	size_t bytes_read_total;
//	ssize_t bytes_read;
//
//	if (!IsValidFD(fd))
//		return (NULL);
//	line_buffer = GetLineBuffer(fd);
//	if (line_buffer->m_BufferSize)
//		ret = ft_strndup(line_buffer->m_Start, line_buffer->m_BufferSize); //This bottlenecks for big BUFFERSIZE with many many small lines
//	else
//		ret = malloc(BUFFER_SIZE);
//	if (!ret) {
//		return (NULL);
//	}
//	bytes_read_total = line_buffer->m_BufferSize;
//	bytes_read = 1;
//	while (1) {
//		line_end = ft_memchr(ret, '\n', bytes_read_total);
//		if (line_end || !bytes_read)
//			return (ProcessLine(ret, line_end, line_buffer, bytes_read_total));
//		line_buffer->m_Start = &(line_buffer->m_Buffer[0]);
//		bytes_read = read(fd, line_buffer->m_Start, BUFFER_SIZE);
//		if (bytes_read < 0)
//			return (CleanUp(ret, line_buffer));
//		line_buffer->m_BufferSize = bytes_read;
//		realloc_temp = ft_realloc(ret, bytes_read_total, bytes_read_total + bytes_read);
//		if (!realloc_temp)
//			return (CleanUp(ret, line_buffer));
//		ret = realloc_temp;
//		ft_memcpy(ret + bytes_read_total, line_buffer->m_Start, bytes_read);
//		bytes_read_total += bytes_read;
//	}
//}
//static char *ProcessLine(char *line, char *line_end, t_line_buffer *line_buffer, size_t size) {
//	char *ret;
//	size_t line_len;
//
//	if (!size)
//		return (CleanUp(line, line_buffer));
//	if (line_end)
//		line_len = line_end - line + 1;
//	else
//		line_len = size;
//	ret = ft_strndup(line, line_len);
//	if (!ret)
//		return (CleanUp(line, line_buffer));
//	line_len = (char*) ft_memchr(line_buffer->m_Start, '\n', line_buffer->m_BufferSize) - line_buffer->m_Start + 1;
//	line_buffer->m_Start += line_len;
//	if (line_buffer->m_BufferSize > line_len) {
//		line_buffer->m_BufferSize -= (line_len);
////		printf("buffer \"%.*s\"\n", (int) line_buffer->m_BufferSize, line_buffer->m_Start);
//	} else
//		line_buffer->m_BufferSize = 0;
//	free(line);
//	return (ret);
//}