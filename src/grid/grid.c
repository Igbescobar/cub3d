/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdurban- <fdurban-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:07:49 by fdurban-          #+#    #+#             */
/*   Updated: 2025/09/01 16:16:32 by fdurban-         ###   ########.fr       */
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

void	paint_grid(t_map map_data, t_mlx mlx_data)
{
	int	i;
	int	j;
	// int	max_cell_height;
	// int	max_cell_width;

	i = 0;
	calculate_square_size(&map_data);
	printf("Valor de width cell %d\n", map_data.cell_width);
	printf("Valor de height cell %d\n", map_data.cell_height);
	while(map_data.map[i])
	{
		j = 0;
		while(map_data.map[i][j])
		{
			while()
			{
				mlx_pixel_put(mlx_data.mlx_ptr,mlx_data.win_ptr, j * map_data.cell_width, i * map_data.cell_height, 0xFFFFFF);
			}
			while()
			{
				mlx_pixel_put(mlx_data.mlx_ptr,mlx_data.win_ptr, j * map_data.cell_width, i * map_data.cell_height, 0xFFFFFF);
			}
			j++;
		}
		i++;
	}
}
