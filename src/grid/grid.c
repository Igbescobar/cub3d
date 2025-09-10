/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdurban- <fdurban-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:07:49 by fdurban-          #+#    #+#             */
/*   Updated: 2025/09/10 17:40:24 by fdurban-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
	char *dst;

	dst = data->map_addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	paint_grid(t_map *map_data, t_mlx mlx_data)
{
	if(mlx_data.mlx_ptr)
		printf("El puntero existe\n");
	map_data->map_img = mlx_new_image(
		mlx_data.mlx_ptr,
		(map_data->map_width * map_data->cell_width),
		(map_data->map_height * map_data->cell_height));
	map_data->map_addr = mlx_get_data_addr(
	map_data->map_img,
	&map_data->bits_per_pixel,
	&map_data->line_length,
	0);
	int	i;
	int	j;
	int	x;
	int	y;
	int	color;

	i = 0;
	while(i < map_data->map_height)
	{
		j = 0;
		while(j < map_data->map_width)
		{
			if (map_data->map[i][j] == '1')
				color = 0xFFFFFF;
			else
				color = 0x000000;
			x = 0;
			while(x < 30)
			{
				y = 0;
				while (y < 30)
				{
					my_mlx_pixel_put(
						map_data, 
						j * 30 + x, 
						i * 30 + y,
						color);
					y++;
				}
				x++;
			}
			j++;
		}
		i++;
	}

	mlx_put_image_to_window(
	mlx_data.mlx_ptr,
	mlx_data.win_ptr,
	map_data->map_img,
	0, 0
	);
}

void	paint_player(t_map *map_data, t_mlx mlx_data)
{
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, map_data->player.player_img, map_data->player.coordinate_x, map_data->player.coordinate_y);
}


