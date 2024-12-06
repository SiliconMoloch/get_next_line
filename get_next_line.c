/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:44:56 by yabokhar          #+#    #+#             */
/*   Updated: 2024/12/05 20:58:04 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*get_next_line(int fd);
static void	set_to_null(char *s);
static void	shift(char *buffer);

char	*get_next_line(int fd)

{
	static char	buffer[BUFFER_SIZE + 1];
	int			bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	line = duplicate(buffer);
	if (!line)
		return (NULL);
	while (bytes_read && !string_contains_newline(buffer))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (set_to_null(buffer), free(line), NULL);
		buffer[bytes_read] = '\0';
		line = concatenate(line, buffer);
		if (!line)
			return (NULL);
	}
	shift(buffer);
	if (!line[0])
		return (free(line), NULL);
	return (line);
}

void	set_to_null(char *s)

{
	while (*s)
	{
		*s = '\0';
		s++;
	}
}

void	shift(char *buffer)

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
