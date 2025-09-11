/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:07:49 by fdurban-          #+#    #+#             */
/*   Updated: 2025/09/11 11:24:44 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void my_mlx_pixel_put(t_map *data, int x, int y, int color)
{
	char *dst;

	dst = data->map_addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	//printf("value of dst is %p\n", dst);
	*(unsigned int*)dst = color;
}

void	paint_grid(t_map *map_data, t_mlx *mlx_data)
{
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
			while(x < map_data->cell_width)
			{
				y = 0;
				while (y < map_data->cell_height)
				{
					my_mlx_pixel_put(
						map_data, 
						j * map_data->cell_width + x, 
						i * map_data->cell_height + y,
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
	mlx_data->mlx_ptr,
	mlx_data->win_ptr,
	map_data->map_img,
	0, 0
	);
}


