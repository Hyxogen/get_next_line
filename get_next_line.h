/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/27 09:32:47 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/10/28 13:16:00 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <wchar.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*ft_strndup(const char *str, size_t len);
void	*ft_memchr(const void *arr, unsigned char c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	*ft_realloc(void *src, size_t old_len, size_t new_len);
char	*ft_strjoin(const char *str1, const char *str2);
void	*ft_memset(void *src, int c, size_t len);

char	*get_next_line(int fd);

typedef struct s_line_buffer {
	char m_Buffer[BUFFER_SIZE];
	char *m_Start;
	char *m_End;
	size_t m_BufferSize;
	ssize_t m_LastRead;
}	t_line_buffer;

# define TRUE 1
# define FALSE 0

#endif
