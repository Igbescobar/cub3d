/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdurban- <fdurban-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:07:49 by fdurban-          #+#    #+#             */
/*   Updated: 2025/09/01 17:13:47 by fdurban-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_square_size(t_map *map_data)
{
	printf("Value of first line of map is %s\n", map_data->map[1]);
	map_data->cell_width = WIN_WIDTH/map_data->map_width;
	map_data->cell_height = WIN_HEIGHT/map_data->map_height;
	printf("Value of x per cell is %d based on %d and %d\n", map_data->cell_width, map_data->map_width, WIN_WIDTH);
}

void paint_grid(t_map map_data, t_mlx mlx_data)
{
	int i;
	int j;
	int x;
	int y;
	calculate_square_size(&map_data);
	// Dibujar líneas verticales (columnas)
	j = 0;
	while (j <= map_data.map_width)
	{
		x = j * map_data.cell_width;
		y = 0;
		while (y < WIN_HEIGHT)
		{
		    mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, x, y, 0xFFFFFF);
		    y++;
		}
		j++;
	}
	// Dibujar líneas horizontales (filas)
	i = 0;
	while (i <= map_data.map_height)
	{
		y = i * map_data.cell_height;
		x = 0;
		while (x < WIN_WIDTH)
		{
		    mlx_pixel_put(mlx_data.mlx_ptr, mlx_data.win_ptr, x, y, 0xFFFFFF);
		    x++;
		}
		i++;
	}
}


