/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/27 09:32:39 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/10/28 13:16:00 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * Custom implementation of libc memchr from libft
 *
 * @brief Finds the first occurrence of c (after conversion to unsigned char as
 * if by (unsigned char)c) in the initial count characters (each interpreted as
 * unsigned char) of the object pointed to by ptr.
 *
 * @param arr pointer to the object to be examined
 * @param c	character to search for
 * @param n	max number of characters to examine
 * @return The ft_memchr() function returns a pointer to the byte located, or
 * NULL if no such byte exists within n bytes.
 */
void
	*ft_memchr(const void *arr, unsigned char c, size_t n)
{
	const unsigned char	*arr_cpy;

	arr_cpy = arr;
	while (n)
	{
		if (*arr_cpy == c)
			return ((void *) arr_cpy);
		if (!*arr_cpy)
			break ;
		n--;
		arr_cpy++;
	}
	return (NULL);
}

/**
 * Custom implementation of libc memcpy from libft
 *
 * @brief Copies count characters from the object pointed to by src to the
 * object pointed to by dest. Both objects are interpreted as arrays of unsigned
 * char.
 *
 * @param dst pointer to the object to copy to
 * @param src pointer to the object to copy from
 * @param len number of bytes to copy
 * @returns Returns a copy of dest
 */
void
	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_cpy;
	const unsigned char	*src_cpy;

	if (dst == src)
		return (dst);
	dst_cpy = dst;
	src_cpy = src;
	while (len)
	{
		dst_cpy[len - 1] = src_cpy[len - 1];
		len--;
	}
	return (dst);
}

/**
 * Custom implementation of libc realloc
 *
 * @brief Reallocates the given area of memory. It must be previously allocated
 * by malloc(), calloc() or realloc() and not yet freed with a call to free or
 * realloc. Otherwise, the results are undefined.
 *
 * @remark If allocation of new memory failed, the old memory block is freed and
 * null pointer is returned.
 * @remark If src is NULL, the behavior is the same as calling malloc(new_len).
 *
 * @param src pointer to the memory area to be reallocated
 * @param old_len old size of the array in bytes
 * @param new_len new size of the array in bytes
 * @return On success, returns the pointer to the beginning of newly allocated
 * memory. To avoid a memory leak, the returned pointer must be deallocated with
 * free() or realloc(). The original pointer ptr is invalidated and any access
 * to it is undefined behavior (even if reallocation was in-place).
 *
 * @return On failure, returns a null pointer. The original pointer ptr is also
 * freed
 */
void
	*ft_realloc(void *src, size_t old_len, size_t new_len)
{
	unsigned char	*ret;

	ret = malloc(new_len);
	if (!ret)
	{
		free(src);
		return (NULL);
	}
	if (src)
	{
		ft_memcpy(ret, src, old_len);
		free(src);
	}
	return (ret);
}

/**
 * Custom implementation of libc memset from libft
 *
 * @brief Copies the value c (after conversion to unsigned char as if by
 * (unsigned char)c) into each of the first count characters of the object
 * pointed to by dest.
 *
 * @param src pointer to the object to fill
 * @param c fill byte
 * @param len number of bytes to fill
 * @return A copy of dest
 */
void
	*ft_memset(void *src, int c, size_t len)
{
	unsigned char	*src_cpy;

	src_cpy = src;
	while (len)
	{
		src_cpy[len - 1] = (unsigned char) c;
		len--;
	}
	return (src);
}
