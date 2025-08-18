/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:17:04 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/18 15:21:24 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_map
{
	char	**map;
	int		map_height;
	int		map_width;
}			t_map;

// ========== Error Handling ==========
int			exit_with_error(const char *message);

// ========== Argument Parsing ==========
int			parsing_handler(int argc, char **argv);
int			has_cub_extension(const char *filename);

// ========== Parsing Sub-functions ==========
int			validate_argument_count(int argc);
int			validate_file_extension(const char *filename);
int			validate_file_access(const char *filename);
int			load_map_from_file(const char *filename, t_map *map_data);
int			validate_characters(t_map *map_data);
int			validate_enclosure(t_map *map_data);
int			validate_player(t_map *map_data);
int			run_all_validations(t_map *map_data);
void		print_success_message(t_map *map_data);

// ========== Map Struct ==========

// ========== Map Parsing ==========
int			parse_map(const char *filename, t_map *map_data);
int			read_map_lines(const char *filename, t_map *map_data);
void		calculate_map_width(t_map *map_data);
void		free_map(t_map *map_data);
int			count_map_lines(const char *filename);

// ========== Parsing Helper Functions ==========
int			allocate_map_memory(t_map *map_data);
int			open_map_file(const char *filename);
char		*process_line(char *line);
int			get_line_width(t_map *map_data, int line_index);
void		update_max_width(t_map *map_data, int current_width);

// ========== Map Validation ==========
int			validate_map_characters(t_map *map_data);
int			validate_enclosed_map(t_map *map_data);
int			validate_player_position(t_map *map_data);

// ========== Helper Functions ==========
int			is_valid_map_character(char c);
int			is_playable_area(char c);
int			is_player_position(char c);
int			is_position_valid(t_map *map_data, int i, int j);
char		get_char_at_position(t_map *map_data, int i, int j);

// ========== Character Validation ==========
int			validate_single_character(t_map *map_data, int i, int j);

// ========== Player Validation ==========
int			count_players_in_line(t_map *map_data, int i);

// ========== Enclosure Validation ==========
int			check_playable_area_enclosure(t_map *map_data);
int			check_adjacent_position(t_map *map_data, int i, int j, int di,
				int dj);
int			check_all_directions(t_map *map_data, int i, int j);
int			validate_single_playable_position(t_map *map_data, int i, int j);
int			check_line_enclosure(t_map *map_data, int i);

#endif
