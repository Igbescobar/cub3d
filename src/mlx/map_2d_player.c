/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2d_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:30:00 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/19 12:10:58 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	get_player_screen_pos(t_mlx *mlx_data, int *screen_x, int *screen_y)
{
	int	offset_x;
	int	offset_y;
	int	player_size;

	calculate_map_center_offset(mlx_data, &offset_x, &offset_y);
	player_size = TILE_SIZE / 2;
	*screen_x = offset_x + (int)(mlx_data->map_data->player.pos_x * TILE_SIZE)
		- player_size / 2;
	*screen_y = offset_y + (int)(mlx_data->map_data->player.pos_y * TILE_SIZE)
		- player_size / 2;
}

void	draw_player_on_map(t_mlx *mlx_data)
{
	int		screen_x;
	int		screen_y;
	int		player_size;
	t_rect	rect;

	get_player_screen_pos(mlx_data, &screen_x, &screen_y);
	player_size = TILE_SIZE / 2;
	rect.x = screen_x;
	rect.y = screen_y;
	rect.width = player_size;
	rect.height = player_size;
	draw_rectangle(mlx_data, rect, MAP_2D_COLOR_PLAYER);
}

void	render_2d_map(t_mlx *mlx_data)
{
	clear_image(mlx_data);
	draw_2d_map_grid(mlx_data);
	draw_player_on_map(mlx_data);
	mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr,
		mlx_data->img_ptr, 0, 0);
}
