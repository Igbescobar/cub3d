/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:13:54 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/22 17:51:06 by igngonza         ###   ########.fr       */
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
		return (exit_with_error("Invalid file extension. \
      Expected a .cub file."));
	return (0);
}

int	validate_file_access(const char *filename)
{
	if (access(filename, F_OK) != 0)
		return (exit_with_error("File does not exist or path is incorrect."));
	if (access(filename, R_OK) != 0)
		return (exit_with_error("File exists but cannot be read. \
      Check file permissions."));
	return (0);
}

int	validate_enclosure(t_map *map_data)
{
	if (check_playable_area_enclosure(map_data) != 0)
	{
		free_map(map_data);
		return (exit_with_error("Map enclosure validation failed."));
	}
	return (0);
}

int	validate_player(t_map *map_data)
{
	if (validate_player_position(map_data) != 0)
	{
		free_map(map_data);
		return (1);
	}
	return (0);
}
