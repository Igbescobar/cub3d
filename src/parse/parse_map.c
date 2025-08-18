/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:45:16 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/18 15:17:56 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	count_map_lines(const char *filename)
{
	int		fd;
	int		line_count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line_count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		line_count++;
		free(line);
	}
	close(fd);
	return (line_count);
}

int	read_map_lines(const char *filename, t_map *map_data)
{
	int		fd;
	int		i;
	char	*line;

	map_data->map_height = count_map_lines(filename);
	if (map_data->map_height <= 0)
		return (0);
	map_data->map = malloc(sizeof(char *) * (map_data->map_height + 1));
	if (!map_data->map)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(map_data->map);
		return (0);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL && i < map_data->map_height)
	{
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map_data->map[i] = line;
		i++;
	}
	map_data->map[i] = NULL;
	close(fd);
	return (1);
}

void	calculate_map_width(t_map *map_data)
{
	int	i;

	map_data->map_width = 0;
	i = 0;
	while (i < map_data->map_height)
	{
		if ((int)ft_strlen(map_data->map[i]) > map_data->map_width)
			map_data->map_width = ft_strlen(map_data->map[i]);
		i++;
	}
}

int	parse_map(const char *filename, t_map *map_data)
{
	if (!read_map_lines(filename, map_data))
		return (0);
	calculate_map_width(map_data);
	return (1);
}

void	free_map(t_map *map_data)
{
	int	i;

	if (!map_data || !map_data->map)
		return ;
	i = 0;
	while (i < map_data->map_height && map_data->map[i])
	{
		free(map_data->map[i]);
		i++;
	}
	free(map_data->map);
	map_data->map = NULL;
	map_data->map_height = 0;
	map_data->map_width = 0;
}

// ========== Memory Management Helper ==========

int	allocate_map_memory(t_map *map_data)
{
	map_data->map = malloc(sizeof(char *) * (map_data->map_height + 1));
	if (!map_data->map)
		return (0);
	return (1);
}

// ========== File Operations Helper ==========

int	open_map_file(const char *filename)
{
	return (open(filename, O_RDONLY));
}

// ========== Line Processing Helper ==========

char	*process_line(char *line)
{
	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

// ========== Enhanced Width Calculation ==========

int	get_line_width(t_map *map_data, int line_index)
{
	if (line_index < 0 || line_index >= map_data->map_height)
		return (0);
	return ((int)ft_strlen(map_data->map[line_index]));
}

void	update_max_width(t_map *map_data, int current_width)
{
	if (current_width > map_data->map_width)
		map_data->map_width = current_width;
}
