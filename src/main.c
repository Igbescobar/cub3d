/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdurban- <fdurban-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:57:19 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/03 17:11:33 by fdurban-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	player_key_hook(int keycode, t_game *game)
{
	if(keycode == XK_w)
	{
		printf("He presionado w\n");
		game->map.player.coordinate_x -= 1;
		mlx_put_image_to_window(
			game->mlx.mlx_ptr,
			game->mlx.win_ptr,
			game->map.player.player_img,
			game->map.player.coordinate_y,
			game->map.player.coordinate_x
		);
	}
	if(keycode == XK_d)
	{
		printf("He presionado d\n");
		game->map.player.coordinate_y += 1;
		mlx_put_image_to_window(
			game->mlx.mlx_ptr,
			game->mlx.win_ptr,
			game->map.player.player_img,
			game->map.player.coordinate_y,
			game->map.player.coordinate_x
		);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	map_data;
	t_mlx	mlx_data;
	t_game	game;

	if (parsing_handler(argc, argv, &map_data) != 0)
	{
		cleanup_get_next_line();
		return (1);
	}
	if (init_mlx_window(&mlx_data, &map_data) != 0)
	{
		free_map(&map_data);
		cleanup_get_next_line();
		return (1);
	}
	calculate_square_size(&map_data);
	paint_grid();
	paint_player(&map_data, mlx_data);
	game.map = map_data;
	game.mlx = mlx_data;
	mlx_key_hook(mlx_data.win_ptr, player_key_hook, &game);
	mlx_loop(mlx_data.mlx_ptr);
	cleanup_mlx(&mlx_data);
	free_map(&map_data);
	return (0);
}
