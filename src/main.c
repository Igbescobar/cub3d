/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdurban- <fdurban-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:57:19 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/09 16:48:38 by fdurban-         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_map	map_data;
	t_mlx	mlx_data;
	t_game	game;
	int		img_width;
	int		player_width;
	int		player_height;
	int		img_height;
	char	*grid_path = "./textures/square.xpm";
	char	*player_path = "./textures/player.xpm";
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
	map_data.cell_width = 20;
	map_data.cell_height = 20;
	map_data.player.player_img = mlx_xpm_file_to_image(mlx_data.mlx_ptr, player_path, &player_width, &player_height);
	map_data.square_img = mlx_xpm_file_to_image(mlx_data.mlx_ptr, grid_path, &img_width, &img_height);
	map_data.player.coordinate_x = map_data.cell_width * map_data.player.pos_x;
	map_data.player.coordinate_y = map_data.cell_height * map_data.player.pos_y;
	game.map = map_data;
	game.mlx = mlx_data;
	game.keys.w = 0;
	game.keys.a = 0;
	game.keys.s = 0;
	game.keys.d = 0;
	game.map.grid_width = map_data.map_width * map_data.cell_width;
	game.map.grid_height = map_data.map_height * map_data.cell_height;
	mlx_hook(game.mlx.win_ptr, KeyPress, KeyPressMask, key_press_handler, &game);
	mlx_hook(game.mlx.win_ptr, KeyRelease, KeyReleaseMask, key_release_handler, &game);
	mlx_loop_hook(mlx_data.mlx_ptr, game_loop, &game);
	mlx_loop(mlx_data.mlx_ptr);
	cleanup_mlx(&mlx_data);
	free_map(&map_data);
	return (0);
}
