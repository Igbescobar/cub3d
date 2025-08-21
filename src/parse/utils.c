/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:20:03 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/21 20:01:50 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	has_cub_extension(const char *filename)
{
	const char	*dot = ft_strrchr(filename, '.');

	if (!dot || dot == filename)
		return (0);
	return (ft_strncmp(dot, ".cub", 4) == 0);
}

void	print_success_message(t_map *map_data)
{
	printf("Map validation successful!\n");
	printf("Map dimensions: %d x %d\n", map_data->map_width,
		map_data->map_height);
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

int	count_map_lines(const char *filename)
{
	int		fd;
	int		map_line_count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	map_line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_map_line(line))
			map_line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map_line_count);
}
