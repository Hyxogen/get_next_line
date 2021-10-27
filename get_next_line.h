#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <wchar.h>

# define NULL 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

char	*ft_strndup(const char *str, size_t len);
char	*ft_strchr(const char *str, char c);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	*ft_realloc(void *src, size_t old_len, size_t new_len);
char	*ft_strjoin(const char *str1, const char *str2)
#endif
