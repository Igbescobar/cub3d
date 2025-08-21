/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:45:16 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/21 20:07:53 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	extract_map_lines_from_file(const char *filename, t_map *map_data)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(map_data->map);
		return (1);
	}
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_map_line(line) && i < map_data->map_height)
			map_data->map[i++] = remove_trailing_newline(line);
		else
			free(line);
		line = get_next_line(fd);
	}
	map_data->map[i] = NULL;
	close(fd);
	return (0);
}

int	read_map_lines(const char *filename, t_map *map_data)
{
	if (allocate_map_array(filename, map_data))
		return (1);
	if (extract_map_lines_from_file(filename, map_data))
		return (1);
	return (0);
}

int	parse_map(const char *filename, t_map *map_data)
{
	if (parse_config_from_file(filename, &map_data->config))
		return (1);
	if (read_map_lines(filename, map_data))
	{
		free_config(&map_data->config);
		return (1);
	}
	calculate_map_width(map_data);
	return (0);
}
