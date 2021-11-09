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

static t_line_buffer
	*get_linebuffer(int fd)
{
	static t_line_buffer	line_buffers[OPEN_MAX];
	t_line_buffer			*ret;

	ret = &line_buffers[fd];
	ret->m_End = &(ret->m_Buffer[BUFFER_SIZE - 1]);
	if (!ret->m_Start)
	{
		ret->m_LastRead = -1;
		ret->m_Start = &ret->m_Buffer[0];
	}
	return (&line_buffers[fd]);
}

static size_t
	get_remaining_size(const t_line_buffer *line_buffer)
{
	if (line_buffer->m_End < (line_buffer->m_Start + line_buffer->m_LastRead))
		return (line_buffer->m_End - line_buffer->m_Start + 1);
	return (line_buffer->m_LastRead);
}

static int
	copy_over(char **dst, size_t *dst_size, t_line_buffer *line_buffer)
{
	char	*ret;

	if (line_buffer->m_LastRead <= 0)
		return (TRUE);
	ret = ft_realloc(*dst, *dst_size,
			  *dst_size + get_remaining_size(line_buffer));
	if (!ret)
	{
		line_buffer->m_LastRead = -1;
		return (FALSE);
	}
	ft_memcpy(ret + *dst_size, line_buffer->m_Start,
		  get_remaining_size(line_buffer));
	*dst_size += get_remaining_size(line_buffer);
	line_buffer->m_Start = &line_buffer->m_Buffer[0];
	*dst = ret;
	return (TRUE);
}

static char
	*process_line(char *tmp, size_t tmp_size, t_line_buffer *line_buffer,
		char *line_end)
{
	size_t	line_len;

	line_len = line_end - line_buffer->m_Start + 1;
	if (tmp || (line_buffer->m_LastRead > 0))
	{
		tmp = ft_realloc(tmp, tmp_size, tmp_size + line_len + 1);
		if (!tmp)
			return (NULL);
		ft_memcpy(tmp + tmp_size, line_buffer->m_Start, line_len);
		if (ft_memchr(line_buffer->m_Start, '\n', line_buffer->m_LastRead))
			tmp[tmp_size + line_len] = '\0';
		else
			tmp[tmp_size + line_len - 1] = '\0';
		line_buffer->m_Start = line_end + 1;
		if (line_buffer->m_Start
			>= (&line_buffer->m_Buffer[0] + line_buffer->m_LastRead))
		{
			line_buffer->m_Start = &line_buffer->m_Buffer[0];
			ft_memset(line_buffer->m_Start, '\0', BUFFER_SIZE);
			line_buffer->m_LastRead = -1;
		}
		return (tmp);
	}
	line_buffer->m_LastRead = -1;
	return (NULL);
}

/**
 * Gets the next line in from a file
 *
 * @param fd a file descriptor from which to get the next line
 * @returns On success returns the next line in the file allocated on the heap
 * or NULL if file end has been reached
 *
 * @returns On failure returns NULL pointer
 */
char
	*get_next_line(int fd)
{
	t_line_buffer	*lb;
	char			*tmp;
	char			*new_line;
	size_t			size;

	if (!((fd >= 0) && (fd <= OPEN_MAX)))
		return (NULL);
	lb = get_linebuffer(fd);
	tmp = NULL;
	size = 0;
	while (1)
	{
		new_line = ft_memchr(lb->m_Start, '\n', get_remaining_size(lb));
		if (new_line)
			return (process_line(tmp, size, lb, new_line));
		if ((lb->m_LastRead >= 0) && (lb->m_LastRead < BUFFER_SIZE))
			return (process_line(tmp, size, lb, lb->m_Start + lb->m_LastRead));
		if (!copy_over(&tmp, &size, lb))
			return (NULL);
		lb->m_LastRead = read(fd, lb->m_Start, BUFFER_SIZE);
		if (lb->m_LastRead < 0)
			break ;
	}
	free(tmp);
	return (NULL);
}