/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:35:37 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/21 20:25:12 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_valid_map_character(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '\n');
}

int	is_playable_area(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_player_position(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_position_valid(t_map *map_data, int i, int j)
{
	if (i < 0 || i >= map_data->map_height)
		return (0);
	if (j < 0 || j >= (int)ft_strlen(map_data->map[i]))
		return (0);
	return (1);
}

char	get_char_at_position(t_map *map_data, int i, int j)
{
	if (!is_position_valid(map_data, i, j))
		return (' ');
	return (map_data->map[i][j]);
}

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
				return (1);
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
	if (player_count != 1)
		return (1);
	return (0);
}

int	check_adjacent_position(t_map *map_data, int i, int j, int di, int dj)
{
	char	adjacent_char;
	int		adj_i;
	int		adj_j;

	adj_i = i + di;
	adj_j = j + dj;
	adjacent_char = get_char_at_position(map_data, adj_i, adj_j);
	if (!is_position_valid(map_data, adj_i, adj_j))
		return (1);
	if (adjacent_char == ' ')
	{
		if (adj_i == 0 || adj_i == map_data->map_height - 1 || adj_j == 0
			|| adj_j >= (int)ft_strlen(map_data->map[adj_i]) - 1)
			return (1);
		return (0);
	}
	return (0);
}

int	check_all_directions(t_map *map_data, int i, int j)
{
	if (check_adjacent_position(map_data, i, j, -1, 0))
		return (1);
	if (check_adjacent_position(map_data, i, j, 1, 0))
		return (1);
	if (check_adjacent_position(map_data, i, j, 0, -1))
		return (1);
	if (check_adjacent_position(map_data, i, j, 0, 1))
		return (1);
	return (0);
}

int	validate_single_playable_position(t_map *map_data, int i, int j)
{
	if (!is_playable_area(map_data->map[i][j]))
		return (0);
	return (check_all_directions(map_data, i, j));
}

int	check_line_enclosure(t_map *map_data, int i)
{
	int	j;

	j = 0;
	while (j < (int)ft_strlen(map_data->map[i]))
	{
		if (validate_single_playable_position(map_data, i, j))
			return (1);
		j++;
	}
	return (0);
}

int	check_playable_area_enclosure(t_map *map_data)
{
	int	i;

	i = 0;
	while (i < map_data->map_height)
	{
		if (check_line_enclosure(map_data, i))
			return (1);
		i++;
	}
	return (0);
}
