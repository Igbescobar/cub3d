/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2d_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:30:00 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/15 18:34:03 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	get_player_screen_pos(t_mlx *mlx_data, int *screen_x, int *screen_y)
{
	int	offset_x;
	int	offset_y;
	int	player_size;

	calculate_map_center_offset(mlx_data, &offset_x, &offset_y);
	player_size = TILE_SIZE / 3;
	*screen_x = offset_x + (int)(mlx_data->map_data->player.pos_x * TILE_SIZE)
		- player_size / 2;
	*screen_y = offset_y + (int)(mlx_data->map_data->player.pos_y * TILE_SIZE)
		- player_size / 2;
}

static void	draw_player_square(t_mlx *mlx_data, int screen_x, int screen_y)
{
	int	player_size;

	player_size = TILE_SIZE / 3;
	draw_rectangle(mlx_data, screen_x, screen_y, player_size, player_size,
		MAP_2D_COLOR_PLAYER);
}

static void	draw_direction_line(t_mlx *mlx_data, int screen_x, int screen_y)
{
	int	player_size;
	int	center_x;
	int	center_y;
	int	end_x;
	int	end_y;
	int	i;
	int	point_x;
	int	point_y;

	player_size = TILE_SIZE / 3;
	center_x = screen_x + player_size / 2;
	center_y = screen_y + player_size / 2;
	end_x = center_x + (int)(mlx_data->map_data->player.dir_x * (TILE_SIZE
				/ 2));
	end_y = center_y + (int)(mlx_data->map_data->player.dir_y * (TILE_SIZE
				/ 2));
	i = 0;
	while (i <= 10)
	{
		point_x = center_x + ((end_x - center_x) * i) / 10;
		point_y = center_y + ((end_y - center_y) * i) / 10;
		put_pixel_to_image(mlx_data, point_x, point_y, 0xFFFF00);
		i++;
	}
}

void	draw_player_on_map(t_mlx *mlx_data)
{
	int	screen_x;
	int	screen_y;

	get_player_screen_pos(mlx_data, &screen_x, &screen_y);
	draw_player_square(mlx_data, screen_x, screen_y);
	draw_direction_line(mlx_data, screen_x, screen_y);
}

void	render_2d_map(t_mlx *mlx_data)
{
	clear_image(mlx_data);
	draw_2d_map_grid(mlx_data);
	draw_player_on_map(mlx_data);
	mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr,
		mlx_data->img_ptr, 0, 0);
}
