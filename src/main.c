/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernando <fernando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:57:19 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/04 16:40:05 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press_handler(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->keys.w = 1;
	if (keycode == XK_a)
		game->keys.a = 1;
	if (keycode == XK_s)
		game->keys.s = 1;
	if (keycode == XK_d)
		game->keys.d = 1;
	return 0;
}

int	key_release_handler(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->keys.w = 0;
	if (keycode == XK_a)
		game->keys.a = 0;
	if (keycode == XK_s)
		game->keys.s = 0;
	if (keycode == XK_d)
		game->keys.d = 0;
	return (0);
}

int game_loop(t_game *game)
{
	if (game->keys.w)
		game->map.player.coordinate_y -= 1;
	if (game->keys.d)
		game->map.player.coordinate_x += 1;
	if (game->keys.a)
		game->map.player.coordinate_x -= 1;
	if (game->keys.s)
		game->map.player.coordinate_y += 1;
	paint_grid(&game->map, game->mlx);
	mlx_put_image_to_window(
		game->mlx.mlx_ptr,
		game->mlx.win_ptr,
		game->map.player.player_img,
		game->map.player.coordinate_x,
		game->map.player.coordinate_y
	);
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
	paint_grid(&map_data, mlx_data);
	paint_player(&map_data, mlx_data);
	game.map = map_data;
	game.mlx = mlx_data;
	game.keys.w = 0;
	game.keys.a = 0;
	game.keys.s = 0;
	game.keys.s = 0;
	mlx_hook(game.mlx.win_ptr, KeyPress, KeyPressMask, key_press_handler, &game);
	mlx_hook(game.mlx.win_ptr, KeyRelease, KeyReleaseMask, key_release_handler, &game);
	mlx_loop_hook(mlx_data.mlx_ptr, game_loop, &game);
	mlx_loop(mlx_data.mlx_ptr);
	cleanup_mlx(&mlx_data);
	free_map(&map_data);
	return (0);
}
