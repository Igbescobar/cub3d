/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_validators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:55:15 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/22 14:56:48 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	get_char_at_position(t_map *map_data, int i, int j)
{
	if (!is_position_valid(map_data, i, j))
		return (' ');
	return (map_data->map[i][j]);
}

int	is_position_valid(t_map *map_data, int i, int j)
{
	if (i < 0 || i >= map_data->map_height)
		return (0);
	if (j < 0 || j >= (int)ft_strlen(map_data->map[i]))
		return (0);
	return (1);
}

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
