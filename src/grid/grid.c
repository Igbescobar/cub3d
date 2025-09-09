/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdurban- <fdurban-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:07:49 by fdurban-          #+#    #+#             */
/*   Updated: 2025/09/09 16:56:01 by fdurban-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	paint_grid(t_map *map_data, t_mlx mlx_data)
{
	int		i;
	int		j;

	i = 0;
	while(map_data->map[i])
	{
		j = 0;
		while(map_data->map[i][j])
		{
			mlx_put_image_to_window(
				mlx_data.mlx_ptr, mlx_data.win_ptr,
				map_data->square_img,
				20 * j,
				20 * i);
			j++;
		}
		i++;
	}
}

void	paint_player(t_map *map_data, t_mlx mlx_data)
{
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, map_data->player.player_img, map_data->player.coordinate_x, map_data->player.coordinate_y);
}


