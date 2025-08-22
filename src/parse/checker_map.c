/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:35:37 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/22 18:02:36 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_map_characters(t_map *map_data)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_data->map_height)
	{
		j = 0;
		while (map_data->map[i][j])
		{
			if (!is_valid_map_character(map_data->map[i][j]))
			{
				free_map(map_data);
				return (exit_with_error("Map validation failed due\
						to invalid characters."));
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_player_position(t_map *map_data)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < map_data->map_height)
	{
		j = 0;
		while (map_data->map[i][j])
		{
			if (is_player_position(map_data->map[i][j]))
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count == 0)
		return (exit_with_error("No player starting position found in map"));
	if (player_count > 1)
		return (exit_with_error("Map must contain exactly one player \
			starting position"));
	return (0);
}

int	is_position_at_map_edge(t_map *map_data, int i, int j)
{
	if (i == 0 || i == map_data->map_height - 1)
		return (1);
	if (j == 0 || j >= (int)ft_strlen(map_data->map[i]) - 1)
		return (1);
	return (0);
}

int	is_safe_adjacent_position(t_map *map_data, int adj_i, int adj_j)
{
	char	adj_char;

	if (!is_position_valid(map_data, adj_i, adj_j))
		return (0);
	adj_char = map_data->map[adj_i][adj_j];
	if (adj_char == '1')
		return (1);
	if (adj_char == '0' || is_player_position(adj_char))
		return (1);
	if (adj_char == ' ' && !is_position_at_map_edge(map_data, adj_i, adj_j))
		return (1);
	return (0);
}

int	check_playable_area_enclosure(t_map *map_data)
{
	int		i;
	int		j;
	char	current_char;

	i = 0;
	while (i < map_data->map_height)
	{
		j = 0;
		while (j < (int)ft_strlen(map_data->map[i]))
		{
			current_char = map_data->map[i][j];
			if (is_playable_area(current_char))
			{
				if (!is_safe_adjacent_position(map_data, i - 1, j)
					|| !is_safe_adjacent_position(map_data, i + 1, j)
					|| !is_safe_adjacent_position(map_data, i, j - 1)
					|| !is_safe_adjacent_position(map_data, i, j + 1))
					return (exit_with_error("Map is not properly enclosed"));
			}
			j++;
		}
		i++;
	}
	return (0);
}
