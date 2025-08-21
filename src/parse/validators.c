/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:13:54 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/21 20:23:00 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_argument_count(int argc)
{
	if (argc != 2)
		return (exit_with_error("Usage: ./cub3d <map_file.cub>"));
	return (0);
}

int	validate_file_extension(const char *filename)
{
	if (!has_cub_extension(filename))
		return (exit_with_error("Invalid file extension. Expected a .cub file."));
	return (0);
}

int	validate_file_access(const char *filename)
{
	if (access(filename, R_OK) != 0)
		return (exit_with_error("Cannot access map file."));
	return (0);
}

int	load_map_from_file(const char *filename, t_map *map_data)
{
	if (parse_map(filename, map_data) != 0)
		return (exit_with_error("Failed to parse map file."));
	return (0);
}

int	validate_characters(t_map *map_data)
{
	if (validate_map_characters(map_data) != 0)
	{
		free_map(map_data);
		return (exit_with_error("Invalid characters found in map."));
	}
	return (0);
}

int	validate_enclosure(t_map *map_data)
{
	if (check_playable_area_enclosure(map_data) != 0)
	{
		free_map(map_data);
		return (exit_with_error("Map is not properly enclosed by walls."));
	}
	return (0);
}

int	validate_player(t_map *map_data)
{
	if (validate_player_position(map_data) != 0)
	{
		free_map(map_data);
		return (exit_with_error("Map must contain exactly one player position (N/S/E/W)."));
	}
	return (0);
}