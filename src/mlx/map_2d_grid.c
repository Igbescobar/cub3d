/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2d_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:30:00 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/15 18:32:43 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_map_center_offset(t_mlx *mlx_data, int *offset_x,
		int *offset_y)
{
	int	total_width;
	int	total_height;

	total_width = mlx_data->map_data->map_width * TILE_SIZE;
	total_height = mlx_data->map_data->map_height * TILE_SIZE;
	*offset_x = (WIN_WIDTH - total_width) / 2;
	*offset_y = (WIN_HEIGHT - total_height) / 2;
	if (*offset_x < 0)
		*offset_x = 0;
	if (*offset_y < 0)
		*offset_y = 0;
}

static int	get_tile_color(char cell)
{
	if (cell == '1')
		return (MAP_2D_COLOR_WALL);
	if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
		return (MAP_2D_COLOR_EMPTY);
	return (0x000000);
}

static void	draw_wall_borders(t_mlx *mlx_data, int x, int y)
{
	int	border_color;

	border_color = 0x654321;
	draw_rectangle(mlx_data, x, y, TILE_SIZE, 1, border_color);
	draw_rectangle(mlx_data, x, y, 1, TILE_SIZE, border_color);
	draw_rectangle(mlx_data, x + TILE_SIZE - 1, y, 1, TILE_SIZE, border_color);
	draw_rectangle(mlx_data, x, y + TILE_SIZE - 1, TILE_SIZE, 1, border_color);
}

static void	draw_single_tile(t_mlx *mlx_data, int map_x, int map_y,
		int offset_x, int offset_y)
{
	int		screen_x;
	int		screen_y;
	char	cell;
	int		color;

	screen_x = offset_x + (map_x * TILE_SIZE);
	screen_y = offset_y + (map_y * TILE_SIZE);
	if (map_x < (int)ft_strlen(mlx_data->map_data->map[map_y]))
		cell = mlx_data->map_data->map[map_y][map_x];
	else
		cell = ' ';
	color = get_tile_color(cell);
	draw_rectangle(mlx_data, screen_x, screen_y, TILE_SIZE, TILE_SIZE, color);
	if (cell == '1')
		draw_wall_borders(mlx_data, screen_x, screen_y);
}

void	draw_2d_map_grid(t_mlx *mlx_data)
{
	int	x;
	int	y;
	int	offset_x;
	int	offset_y;

	calculate_map_center_offset(mlx_data, &offset_x, &offset_y);
	y = 0;
	while (y < mlx_data->map_data->map_height)
	{
		x = 0;
		while (x < mlx_data->map_data->map_width)
		{
			draw_single_tile(mlx_data, x, y, offset_x, offset_y);
			x++;
		}
		y++;
	}
}
