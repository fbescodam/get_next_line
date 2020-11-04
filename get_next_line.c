/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 16:16:20 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/04 17:01:18 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	add_to_line(char **line, unsigned long long line_size, void *buff)
{
	char				*temp;
	unsigned long long	buff_size_nl;
	void				*nl;

	nl = ft_memchr(buff, '\n', BUFFER_SIZE);
	if (nl)
		buff_size_nl = nl - buff;
	else
		buff_size_nl = BUFFER_SIZE;
	temp = (char *)malloc((line_size + buff_size_nl + 1) * sizeof(char));
	if (temp)
	{
		if (*line)
		{
			ft_memcpy(temp, *line, line_size);
			free(*line);
		}
		ft_memcpy(temp + line_size, buff, buff_size_nl);
		temp[line_size + buff_size_nl] = '\0';
		*line = temp;
		if (buff_size_nl < BUFFER_SIZE)
			return (0);
		return (buff_size_nl);
	}
	return (-1);
}

int			get_next_line(int fd, char **line)
{
	void				*buff;
	unsigned long long	read_bytes;
	unsigned long long	line_size;
	int					ret;

	if (BUFFER_SIZE < 1)
		return (-1);
	if (fd >= 0)
	{
		buff = (void *)malloc(BUFFER_SIZE);
		ft_bzero(buff, BUFFER_SIZE);
		read_bytes = read(fd, buff, BUFFER_SIZE);
		line_size = 0;
		while (read_bytes > 0)
		{
			ret = add_to_line(line, line_size, buff);
			if (ret > 0)
				line_size += ret;
			else if (ret == 0)
				return (1);
			else
				return (-1);
			read_bytes = read(fd, buff, BUFFER_SIZE);
		}
		return (0);
	}
	else
		return (-1);
}
