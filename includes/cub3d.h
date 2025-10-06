/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igbescobar <igbescobar@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:17:04 by igngonza          #+#    #+#             */
/*   Updated: 2025/10/06 13:21:12 by igbescobar       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "get_next_line.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// ========== MLX Defines ==========
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define ESC_KEY 65307

// ========== 2D Map Defines ==========
# define TILE_SIZE 20
# define MAP_2D_COLOR_WALL 0x8B4513
# define MAP_2D_COLOR_EMPTY 0xF5F5DC
# define MAP_2D_COLOR_PLAYER 0xFF0000
# define MAP_2D_OFFSET_X 50
# define MAP_2D_OFFSET_Y 50
// ========== Movement ==========
# define MOVE_SPEED 0.05
# define ROTATION_SPEED 0.04

// ========== Texture Defines ==========
# define TEXTURE_NORTH 0
# define TEXTURE_SOUTH 1
# define TEXTURE_WEST 2
# define TEXTURE_EAST 3

typedef struct s_config
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			floor_color[3];
	int			ceiling_color[3];
}				t_config;

// ========== Rectangle Structure ==========
typedef struct s_rect
{
	int			x;
	int			y;
	int			width;
	int			height;
}				t_rect;

// ========== Offset Structure ==========
typedef struct s_offset
{
	int			x;
	int			y;
}				t_offset;

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

// ========== Key State Structure ==========
typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			m;
	int			escape;
	int			left;
	int			right;
	int			up;
	int			down;
}				t_keys;

typedef struct s_map
{
	char		**map;
	int			map_height;
	int			map_width;
	t_config	config;
	t_player	player;
}				t_map;

// ========== Texture Structure ==========
typedef struct s_texture
{
	void		*img_ptr;
	char		*img_data;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_texture;

// ========== Ray Structure ==========
typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

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
	t_texture	textures[4];
	t_keys		keys;
	int			show_2d_map;
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
int				init_mlx_display(t_mlx *mlx_data);
int				setup_mlx_hooks(t_mlx *mlx_data);
void			init_keys(t_keys *keys);
int				key_press_handler(int keycode, t_mlx *mlx_data);
int				key_release_handler(int keycode, t_mlx *mlx_data);
int				game_loop(t_mlx *mlx_data);
int				close_window(t_mlx *mlx_data);
void			cleanup_mlx(t_mlx *mlx_data);
int				handle_continuous_movement(t_mlx *mlx_data);
int				is_valid_position(t_mlx *mlx_data, double new_x, double new_y);

// ========== Texture Functions ==========
int				load_textures(t_mlx *mlx_data, t_config *config);
int				load_single_texture(t_mlx *mlx_data, t_texture *texture,
					char *path);
void			cleanup_textures(t_mlx *mlx_data);
int				validate_texture_files(t_config *config);

// ========== Player Functions ==========
int				init_player(t_map *map_data);
void			set_player_direction(t_player *player, char orientation);
int				find_player_position(t_map *map_data, int *x, int *y,
					char *orientation);
void			set_north_direction(t_player *player);
void			set_south_direction(t_player *player);
void			set_east_direction(t_player *player);
void			set_west_direction(t_player *player);

// ========== Player Movement Functions ==========
void			move_player(t_mlx *mlx_data, double move_x, double move_y);
void			move_forward(t_mlx *mlx_data);
void			move_backward(t_mlx *mlx_data);
void			strafe_left(t_mlx *mlx_data);
void			strafe_right(t_mlx *mlx_data);
void			rotate_player(t_player *player, double angle);

// ========== Raycasting Functions ==========
// Main raycasting controller
void			cast_rays(t_mlx *mlx, t_map *map_data);

// Ray initialization
void			init_ray(t_ray *ray, t_player *player, int x);
void			calculate_step_and_side_dist(t_ray *ray, t_player *player);

// DDA algorithm
void			perform_dda(t_ray *ray, t_map *map_data);

// Wall calculations
void			calculate_distance_and_height(t_ray *ray, t_player *player);
double			calculate_wall_x(t_ray *ray, t_player *player);

// Texture mapping
int				get_texture_index(t_ray *ray);
int				get_texture_pixel(t_mlx *mlx, int tex_index, int tex_x, int tex_y);
int				calculate_texture_x(t_mlx *mlx, t_ray *ray, double wall_x, int tex_index);

// Wall rendering
void			draw_textured_wall(t_mlx *mlx, int x, t_ray *ray, t_player *player);
void			draw_vertical_line(t_mlx *mlx, int x, t_ray *ray, t_map *map_data);

// Utility functions
int				create_rgb_from_config(int color_array[3]);
int				clamp_texture_coordinate(int coord, int max_val);
int				validate_ray_direction(t_ray *ray);
double			calculate_camera_x(int x);

// ========== 2D Map Rendering ==========
void			render_2d_map(t_mlx *mlx_data);
void			draw_2d_map_grid(t_mlx *mlx_data);
void			draw_player_on_map(t_mlx *mlx_data);
void			clear_image(t_mlx *mlx_data);
void			calculate_map_center_offset(t_mlx *mlx_data, int *offset_x,
					int *offset_y);

// ========== Pixel Utilities ==========
void			put_pixel_to_image(t_mlx *mlx_data, int x, int y, int color);
void			draw_rectangle(t_mlx *mlx_data, t_rect rect, int color);
int				create_rgb_color(int r, int g, int b);

// ========== Cleanup Functions ==========
void			cleanup_get_next_line(void);

#endif
