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

#include "get_next_line.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

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
	if (!ret->m_Start) {
		ret->m_LastRead = -1;
		ret->m_Start = &ret->m_Buffer[0];
	}
	return (&line_buffers[fd]);
}

static int IsValidFD(int fd) {
	return ((fd >= 0) && (fd <= OPEN_MAX));
}

static size_t GetRemainingSize(const t_line_buffer *line_buffer) {
	return (line_buffer->m_End - line_buffer->m_Start + 1);
}

static int CopyOver(char **dst, size_t dst_size, t_line_buffer *line_buffer) {
	char *ret;

	if (line_buffer->m_LastRead <= 0)
		return (TRUE);
//	ret = ft_realloc(*dst, dst_size, dst_size + GetRemainingSize(line_buffer));
	ret = ft_realloc(*dst, dst_size, dst_size + line_buffer->m_LastRead);
	if (!ret) {
		free(*dst);
		return (FALSE);
	}
//	ft_memcpy(ret + dst_size, line_buffer->m_Start, GetRemainingSize(line_buffer));
	ft_memcpy(ret + dst_size, line_buffer->m_Start, line_buffer->m_LastRead);
	line_buffer->m_Start = &line_buffer->m_Buffer[0];
	*dst = ret;
	return (TRUE);
}

static char *ProcessLine(char *tmp, size_t tmp_size, t_line_buffer *line_buffer, char *line_end) {
	char *ret;
	size_t line_len;

	ret = NULL;
	line_len = line_end - line_buffer->m_Start + 1;
	if (!tmp && line_buffer->m_LastRead <= 0)
		return (NULL);
	else if (!tmp) {
		ret = ft_strndup(line_buffer->m_Start, line_len);
		if (!ret) {
			free(tmp);
			return (NULL);
		}
		line_buffer->m_Start = line_end + 1;
		if (line_buffer->m_Start >= (&line_buffer->m_Buffer[0] + line_buffer->m_LastRead)) {
			line_buffer->m_Start = &line_buffer->m_Buffer[0];
			ft_memset(line_buffer->m_Start, '\0', BUFFER_SIZE);
			line_buffer->m_LastRead = -1;
		}
		return (ret);
	} else {
		ret = ft_realloc(tmp, tmp_size, tmp_size + line_buffer->m_LastRead);
		if (!ret) {
			free(tmp);
			return (NULL);
		}
		ft_memcpy(tmp + tmp_size, line_buffer->m_Start, line_buffer->m_LastRead);
		line_buffer->m_Start = line_end + 1;
		if (line_buffer->m_Start >= (&line_buffer->m_Buffer[0] + line_buffer->m_LastRead)) {
			line_buffer->m_Start = &line_buffer->m_Buffer[0];
			ft_memset(line_buffer->m_Start, '\0', BUFFER_SIZE);
			line_buffer->m_LastRead = -1;
		}
		return (ret);
	}
}

char *get_next_line(int fd) {
	t_line_buffer *line_buffer;
	char *tmp;
	char *new_line;
	size_t tmp_size;

	if (!IsValidFD(fd))
		return (NULL);
	line_buffer = GetLineBuffer(fd);
	tmp = NULL;
	tmp_size = 0;
	while (1) {
		new_line = ft_memchr(line_buffer->m_Start, '\n', GetRemainingSize(line_buffer));
		if (new_line)
			return (ProcessLine(tmp, tmp_size, line_buffer, new_line));
		if ((line_buffer->m_LastRead >=0) && (line_buffer->m_LastRead < BUFFER_SIZE))
			return (ProcessLine(tmp, tmp_size, line_buffer, line_buffer->m_Start + line_buffer->m_LastRead));
		if (!CopyOver(&tmp, tmp_size, line_buffer))
			return (NULL);
		line_buffer->m_LastRead = read(fd, line_buffer->m_Start, BUFFER_SIZE);
		if (line_buffer->m_LastRead < 0) {
			free(tmp);
			return (NULL);
		}
	}
}