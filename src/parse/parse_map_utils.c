/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:57:53 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/21 20:07:55 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map(t_map *map_data)
{
	int	i;

	if (!map_data)
		return ;
	if (map_data->map)
	{
		i = 0;
		while (i < map_data->map_height && map_data->map[i])
		{
			free(map_data->map[i]);
			i++;
		}
		free(map_data->map);
		map_data->map = NULL;
	}
	free_config(&map_data->config);
	map_data->map_height = 0;
	map_data->map_width = 0;
}

int	allocate_map_array(const char *filename, t_map *map_data)
{
	map_data->map_height = count_map_lines(filename);
	if (map_data->map_height <= 0)
		return (1);
	map_data->map = malloc(sizeof(char *) * (map_data->map_height + 1));
	if (!map_data->map)
		return (1);
	return (0);
}

char	*remove_trailing_newline(char *line)
{
	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}
