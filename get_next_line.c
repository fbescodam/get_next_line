/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 15:30:52 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/11 16:12:07 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	handle_buffer(char **line, size_t *line_length, char *buff, size_t *start)
{
	char			*temp;
	size_t			bytes_to_copy;

	printf("start: %ld\n", *start);
	if (*start > BUFFER_SIZE)
	{
		*start = 0;
		return (BUFFER_SIZE);
	}
	bytes_to_copy = ft_strllen(buff + *start, BUFFER_SIZE - *start);
	printf("bytes_to_copy: %ld\n", bytes_to_copy);
	printf("line_length: %ld\n", *line_length);
	temp = (char *)malloc((*line_length + bytes_to_copy + 1) * sizeof(char));
	if (*line && line_length > 0)
	{
		printf("now copying old string\n");
		ft_strlcpy(temp, *line, *line_length);
		free(*line);
	}
	printf("now copying buffer\n");
	if (bytes_to_copy > 0)
		ft_strlcpy(temp + *line_length, buff + *start, bytes_to_copy);
	else
		temp[0] = '\0';
	*line = temp;
	*line_length += bytes_to_copy;
	if (bytes_to_copy + 1 < BUFFER_SIZE)
		*start += bytes_to_copy + 1;
	else
	{
		ft_bzero(buff, BUFFER_SIZE);
		*start = 0;
	}
	return (bytes_to_copy);
}

int		get_next_line(int fd, char **line)
{
	static void		*buff;
	static size_t	start;
	ssize_t			read_bytes;
	size_t			line_length;

	if (!buff)
	{
		buff = malloc(BUFFER_SIZE);
		if (buff)
			ft_bzero(buff, BUFFER_SIZE);
		else
			return (-1);
		read_bytes = read(fd, buff, BUFFER_SIZE);
	}
	line_length = 0;
	while (read_bytes > 0)
	{
		replace_newlines((char *)buff);
		if (handle_buffer(line, &line_length, buff, &start) < BUFFER_SIZE)
			return (1);
		read_bytes = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	if (read_bytes < 0)
		return (-1);
	return (0);
}
