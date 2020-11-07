/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 16:16:40 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/04 17:13:54 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		c_cpy;
	const unsigned char	*s_cpy;

	c_cpy = c;
	s_cpy = s;
	while (n > 0)
	{
		if (*s_cpy == c_cpy)
			return ((void *)s_cpy);
		s_cpy++;
		n--;
	}
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest_cpy;
	const char	*src_cpy;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_cpy = dest;
	src_cpy = src;
	while (n > 0)
	{
		*dest_cpy = *src_cpy;
		dest_cpy++;
		src_cpy++;
		n--;
	}
	return (dest);
}

void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		*(char *)s = '\0';
		s++;
		n--;
	}
}
