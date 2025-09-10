/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdurban- <fdurban-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:57:19 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/10 17:45:28 by fdurban-         ###   ########.fr       */
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
	paint_player(&game->map, game->mlx);
	return (0);
}

void	initialize_game_values(t_game *game, t_map map_data, t_mlx mlx_data)
{
	game->map = map_data;
	game->mlx = mlx_data;
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
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
	};
	map_data.cell_width = 20;
	map_data.cell_height = 20;
	map_data.line_length = mlx_get_data_addr(mlx_data.img_ptr, map_data.bits_per_pixel, );
	initialize_game_values(&game, map_data, mlx_data);
	mlx_hook(game.mlx.win_ptr, KeyPress, KeyPressMask, key_press_handler, &game);
	mlx_hook(game.mlx.win_ptr, KeyRelease, KeyReleaseMask, key_release_handler, &game);
	mlx_loop_hook(mlx_data.mlx_ptr, game_loop, &game);
	mlx_loop(mlx_data.mlx_ptr);
	cleanup_mlx(&mlx_data);
	free_map(&map_data);
	return (0);
}
