/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 16:16:38 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/18 16:45:20 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_strlcpy_nl(char *dest, const char *src, size_t size);
size_t		ft_strlen_nl(const char *s, size_t maxlen);
int			get_next_line(int fd, char **line);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif
