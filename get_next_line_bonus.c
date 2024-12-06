/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:44:56 by yabokhar          #+#    #+#             */
/*   Updated: 2024/12/06 12:10:21 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char		*get_next_line(int fd);
static void	set_to_null(char *s);
static void	shift(char *buffer);

char	*get_next_line(int fd)

{
	static char	buffer[FD_MAX][BUFFER_SIZE + 1];
	int			bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	line = duplicate(buffer[fd]);
	if (!line)
		return (NULL);
	while (bytes_read && !string_contains_newline(buffer[fd]))
	{
		bytes_read = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes_read < 0)
			return (set_to_null(buffer[fd]), free(line), NULL);
		buffer[fd][bytes_read] = '\0';
		line = concatenate(line, buffer[fd]);
		if (!line)
			return (NULL);
	}
	shift(buffer[fd]);
	if (!line[0])
		return (free(line), NULL);
	return (line);
}

static void	set_to_null(char *s)

{
	while (*s)
	{
		*s = '\0';
		s++;
	}
}

static void	shift(char *buffer)

{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (buffer[i + j])
	{
		buffer[j] = buffer[i + j];
		j++;
	}
	buffer[j] = '\0';
}
