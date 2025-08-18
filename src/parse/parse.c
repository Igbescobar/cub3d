/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:36:45 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/18 15:18:51 by igngonza         ###   ########.fr       */
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
	if (!parse_map(filename, map_data))
		return (exit_with_error("Failed to parse map file."));
	return (0);
}

int	validate_characters(t_map *map_data)
{
	if (validate_map_characters(map_data) != 1)
	{
		free_map(map_data);
		return (exit_with_error("Invalid characters found in map."));
	}
	return (0);
}

int	validate_enclosure(t_map *map_data)
{
	if (validate_enclosed_map(map_data) != 0)
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

int	run_all_validations(t_map *map_data)
{
	if (validate_characters(map_data) != 0)
		return (1);
	if (validate_enclosure(map_data) != 0)
		return (1);
	if (validate_player(map_data) != 0)
		return (1);
	return (0);
}

// ========== Success Reporting ==========

void	print_success_message(t_map *map_data)
{
	printf("Map validation successful!\n");
	printf("Map dimensions: %d x %d\n", map_data->map_width,
		map_data->map_height);
}

// ========== Main Parsing Handler ==========

int	parsing_handler(int argc, char **argv)
{
	t_map	map_data;

	if (validate_argument_count(argc) != 0)
		return (1);
	if (validate_file_extension(argv[1]) != 0)
		return (1);
	if (validate_file_access(argv[1]) != 0)
		return (1);
	if (load_map_from_file(argv[1], &map_data) != 0)
		return (1);
	if (run_all_validations(&map_data) != 0)
		return (1);
	print_success_message(&map_data);
	free_map(&map_data);
	return (0);
}
