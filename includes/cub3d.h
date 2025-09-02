/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdurban- <fdurban-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:17:04 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/02 17:17:04 by fdurban-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_config
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			floor_color[3];
	int			ceiling_color[3];
}				t_config;

// ========== Player Structure ==========
typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_map
{
	char		**map;
	int			map_height;
	int			map_width;
	int			cell_width;
	int			cell_height;
	t_config	config;
	t_player	player;
}				t_map;

// ========== MLX Defines ==========
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define ESC_KEY 65307

// ========== MLX Structures ==========
typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_data;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_map		*map_data;
}				t_mlx;

// ========== Error Handling ==========
int				exit_with_error(const char *message);

// ========== Argument Parsing ==========
int				parsing_handler(int argc, char **argv, t_map *map_data);
int				has_cub_extension(const char *filename);

// ========== Parsing Sub-functions ==========
int				validate_argument_count(int argc);
int				validate_file_extension(const char *filename);
int				validate_file_access(const char *filename);
int				load_map_from_file(const char *filename, t_map *map_data);
int				validate_enclosure(t_map *map_data);
int				validate_player(t_map *map_data);
int				run_all_validations(t_map *map_data);
void			print_success_message(t_map *map_data);

// ========== Map Parsing ==========
int				parse_map(const char *filename, t_map *map_data);
int				read_map_lines(const char *filename, t_map *map_data);
void			calculate_map_width(t_map *map_data);
void			free_map(t_map *map_data);
int				count_map_lines(const char *filename);
int				is_map_line(char *line);

// ========== Configuration Parsing ==========
void			init_config(t_config *config);
int				parse_config_from_file(const char *filename, t_config *config);
int				parse_config_line(char *line, t_config *config);
int				is_config_incomplete(t_config *config);
void			free_config(t_config *config);
char			*skip_whitespace(char *str);
char			*extract_path(char *line);
int				parse_rgb_colors(char *line, int colors[3]);
int				parse_texture_line(char *line, char **texture_ptr);
int				parse_color_line(char *line, int color[3]);
int				process_line(char *line, t_config *config, int *map_started,
					int *map_ended);

// ========== Parsing Map Functions ==========
char			*remove_trailing_newline(char *line);
int				allocate_map_array(const char *filename, t_map *map_data);

// ========== Map Validation ==========
int				validate_map_characters(t_map *map_data);
int				validate_player_position(t_map *map_data);
int				check_playable_area_enclosure(t_map *map_data);

// ========== Helper Functions ==========
int				is_valid_map_character(char c);
int				is_playable_area(char c);
int				is_player_position(char c);
int				is_position_valid(t_map *map_data, int i, int j);
char			get_char_at_position(t_map *map_data, int i, int j);
int				is_valid_texture_path(char *path);

// ========== Enclosure Validation ==========
int				check_playable_area_enclosure(t_map *map_data);
int				is_position_at_map_edge(t_map *map_data, int i, int j);
int				is_safe_adjacent_position(t_map *map_data, int adj_i,
					int adj_j);

// ========== MLX Functions ==========
int				init_mlx_window(t_mlx *mlx_data, t_map *map_data);
int				key_hook(int keycode, t_mlx *mlx_data);
int				close_window(t_mlx *mlx_data);
void			cleanup_mlx(t_mlx *mlx_data);

// ========== Player Functions ==========
int				init_player(t_map *map_data);
void			set_player_direction(t_player *player, char orientation);
int				find_player_position(t_map *map_data, int *x, int *y,
					char *orientation);
void			set_north_direction(t_player *player);
void			set_south_direction(t_player *player);
void			set_east_direction(t_player *player);
void			set_west_direction(t_player *player);

// ========== Cleanup Functions ==========
void			cleanup_get_next_line(void);

void	paint_grid(t_map map_data, t_mlx mlx_data);
void	calculate_square_size(t_map *map_data);
void	paint_player(t_map map_data, t_mlx mlx_data);

#endif
