/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:07:49 by fdurban-          #+#    #+#             */
/*   Updated: 2025/09/04 11:40:47 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_square_size(t_map *map_data)
{
	printf("Value of first line of map is %s\n", map_data->map[1]);
	map_data->cell_width = WIN_WIDTH/map_data->map_width;
	map_data->cell_height = WIN_HEIGHT/map_data->map_height;
	printf("Value of x per cell is %d based on %d and %d\n", map_data->cell_width, map_data->cell_height, WIN_WIDTH);
}

//Cambiar absolutamente todo por imagenes
void	paint_grid(t_map *map_data, t_mlx mlx_data)
{
	char	*relative_path = "./textures/square.xpm";
	int		img_width;
	int		img_height;
	map_data->square_img = mlx_xpm_file_to_image(mlx_data.mlx_ptr, relative_path, &img_width, &img_height);
	int		i = 0;
	while(map_data->map[i])
	{
		int		j = 0;
		while(map_data->map[i][j])
		{
			mlx_put_image_to_window(
				mlx_data.mlx_ptr, mlx_data.win_ptr,
				map_data->square_img,
				map_data->cell_width * j,
				map_data->cell_height * i);
			j++;
		}
		i++;
	}
}

void	paint_player(t_map *map_data, t_mlx mlx_data)
{
	char	*relative_path = "./textures/player.xpm";
	int		img_width;
	int		img_height;
	map_data->player.player_img = mlx_xpm_file_to_image(mlx_data.mlx_ptr, relative_path, &img_width, &img_height);
	printf("al posicion en el eje y del jugador es de %f\n", map_data->player.pos_y);
	map_data->player.coordinate_x = map_data->cell_width * map_data->player.pos_x;
	map_data->player.coordinate_y = map_data->cell_height * map_data->player.pos_y;
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, map_data->player.player_img, map_data->player.coordinate_x, map_data->player.coordinate_y);
}


