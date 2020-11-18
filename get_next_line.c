/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 15:30:52 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/18 17:20:36 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	init_gnl(int fd, char **line, void **buff, ssize_t *read_bytes)
{
	if (fd < 0 || BUFFER_SIZE < 1 || line == NULL)
		return (-1);
	if (!*buff)
	{
		*buff = ft_calloc(sizeof(char), BUFFER_SIZE);
		if (!*buff)
			return (-1);
		*read_bytes = read(fd, *buff, BUFFER_SIZE);
	}
	*line = NULL;
	return (0);
}

static int	handle_buff(char **line, size_t *size,
				char *buff, size_t read_bytes)
{
	static size_t	start;
	char			*temp;
	size_t			bytes_to_copy;

	bytes_to_copy = ft_strlen_nl(buff + start, read_bytes - start);
	temp = (char *)ft_calloc(sizeof(char), (*size + bytes_to_copy + 1));
	if (!temp)
		return (-1);
	if (*line)
	{
		ft_strlcpy_nl(temp, *line, *size);
		free(*line);
	}
	if (bytes_to_copy > 0)
		ft_strlcpy_nl(temp + *size, buff + start, bytes_to_copy);
	*line = temp;
	*size += bytes_to_copy;
	if (bytes_to_copy < read_bytes - start)
	{
		start += bytes_to_copy + 1;
		return (1);
	}
	ft_bzero(buff, BUFFER_SIZE);
	start = 0;
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static void		*buff;
	static ssize_t	read_bytes;
	size_t			size;
	int				handle_result;

	if (init_gnl(fd, line, &buff, &read_bytes) == -1)
		return (-1);
	size = 0;
	while (read_bytes > 0)
	{
		handle_result = handle_buff(line, &size, buff, read_bytes);
		if (handle_result > 0)
			return (1);
		else if (handle_result < 0)
			break ;
		read_bytes = read(fd, buff, BUFFER_SIZE);
	}
	if (!*line)
		*line = ft_calloc(sizeof(char), 1);
	free(buff);
	if (read_bytes < 0 || handle_result < 0)
		return (-1);
	return (0);
}
