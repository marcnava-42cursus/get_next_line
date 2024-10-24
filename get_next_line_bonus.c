/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:48:08 by marcnava          #+#    #+#             */
/*   Updated: 2024/10/24 17:38:14 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_get_line_buffer(int fd, char *pending_line, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(pending_line);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		if (!pending_line)
			pending_line = ft_strdup("");
		tmp = pending_line;
		pending_line = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (pending_line);
}

static char	*ft_get_eol(char *buffer)
{
	char	*pending_line;
	ssize_t	i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == 0 || buffer[i + 1] == 0)
		return (NULL);
	pending_line = ft_substr(buffer, i + 1, ft_strlen(buffer) - 1);
	if (pending_line == 0)
		free(pending_line);
	buffer[i + 1] = 0;
	return (pending_line);
}

char	*get_next_line(int fd)
{
	static char	*pending_line[MAX_FD];
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(pending_line[fd]);
		pending_line[fd] = NULL;
		return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = ft_get_line_buffer(fd, pending_line[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	pending_line[fd] = ft_get_eol(line);
	return (line);
}
