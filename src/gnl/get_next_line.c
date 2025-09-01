/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:00:35 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/01 13:16:55 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_append(buffer, buf);
	free(buffer);
	return (temp);
}

char	*ft_remove_excess_line(char *buffer)
{
	int		i;
	int		j;
	char	*solution;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	solution = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	j = 0;
	i++;
	while (buffer[i])
	{
		solution[j] = buffer[i];
		j++;
		i++;
	}
	free(buffer);
	return (solution);
}

char	*ft_new_line_finder(char *solution_buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!solution_buffer[i])
		return (NULL);
	while (solution_buffer[i] && solution_buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (solution_buffer[i] && solution_buffer[i] != '\n')
	{
		line[i] = solution_buffer[i];
		i++;
	}
	if (solution_buffer[i] && solution_buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *solution_buffer)
{
	char	*buffer;
	int		byte_read;

	if (!solution_buffer)
		solution_buffer = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(solution_buffer);
			free(buffer);
			return (NULL);
		}
		buffer[byte_read] = 0;
		solution_buffer = ft_free(solution_buffer, buffer);
		if (ft_strchr(solution_buffer, '\n'))
			break ;
	}
	free(buffer);
	return (solution_buffer);
}

char	*get_next_line(int fd)
{
	static char	*solution_buffer;
	char		*extracted_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (solution_buffer)
		{
			free(solution_buffer);
			solution_buffer = NULL;
		}
		return (NULL);
	}
	solution_buffer = read_file(fd, solution_buffer);
	if (!solution_buffer)
		return (NULL);
	extracted_line = ft_new_line_finder(solution_buffer);
	solution_buffer = ft_remove_excess_line(solution_buffer);
	return (extracted_line);
}
