/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdurban- <fdurban-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:57:19 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/12 16:53:59 by fdurban-         ###   ########.fr       */
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
	printf("The coordinates x of the player are %f\n", game->map->player.pos_x);
	printf("The coordinates y of the player are %f\n", game->map->player.pos_y);
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
	if (game->keys.w && !is_wall(*game->map, game->map->player.pos_x, game->map->player.pos_y))
		game->map->player.pos_y -= 0.01;
	if (game->keys.d && !is_wall(*game->map, game->map->player.pos_x, game->map->player.pos_y))
		game->map->player.pos_x += 0.01;
	if (game->keys.a && !is_wall(*game->map, game->map->player.pos_x, game->map->player.pos_y))
		game->map->player.pos_x -= 0.01;
	if (game->keys.s && !is_wall(*game->map, game->map->player.pos_x, game->map->player.pos_y))
		game->map->player.pos_y += 0.01;
	game->map->player.coordinate_x = game->map->player.pos_x * game->map->cell_width;
	game->map->player.coordinate_y = game->map->player.pos_y * game->map->cell_height;
	paint_grid(game->map, game->mlx);
	return (0);
}

void	initialize_game_values(t_game *game, t_map *map_data, t_mlx *mlx_data)
{
	game->map = map_data;
	game->mlx = mlx_data;
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->map->cell_width = 30;
	game->map->cell_height = 30;
	game->map->player.coordinate_x = game->map->cell_width * map_data->player.pos_x;
	game->map->player.coordinate_y = game->map->cell_height * map_data->player.pos_y;
}

void	start_2d_image(t_map *map_data,t_mlx *mlx_data)
{
	map_data->map_img = mlx_new_image(
		mlx_data->mlx_ptr,
		(map_data->map_width * map_data->cell_width),
		(map_data->map_height * map_data->cell_height));
	map_data->map_addr = mlx_get_data_addr(
	map_data->map_img,
	&map_data->bits_per_pixel,
	&map_data->line_length,
	&map_data->endian);
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
	initialize_game_values(&game, &map_data, &mlx_data);
	start_2d_image(&map_data, &mlx_data);
	printf("Entra\n");
	mlx_hook(game.mlx->win_ptr, KeyPress, KeyPressMask, key_press_handler, &game);
	mlx_hook(game.mlx->win_ptr, KeyRelease, KeyReleaseMask, key_release_handler, &game);
	mlx_loop_hook(mlx_data.mlx_ptr, game_loop, &game);
	mlx_loop(mlx_data.mlx_ptr);
	cleanup_mlx(&mlx_data);
	free_map(&map_data);
	return (0);
}
