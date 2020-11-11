/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 16:16:38 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/11 17:23:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

void		ft_bzero(void *s, size_t n);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t n);
size_t		ft_strllen(const char *s, size_t maxlen);
void		replace_newlines(char *buff);
int			get_next_line(int fd, char **line);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 20
#endif
