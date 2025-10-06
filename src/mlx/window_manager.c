/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igbescobar <igbescobar@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:00:00 by igngonza          #+#    #+#             */
/*   Updated: 2025/10/06 09:50:43 by igbescobar       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_mlx_display(t_mlx *mlx_data)
{
	mlx_data->mlx_ptr = mlx_init();
	if (!mlx_data->mlx_ptr)
		return (exit_with_error("Failed to initialize MLX"));
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
			"cub3D");
	if (!mlx_data->win_ptr)
	{
		cleanup_mlx(mlx_data);
		return (exit_with_error("Failed to create MLX window"));
	}
	mlx_data->img_ptr = mlx_new_image(mlx_data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx_data->img_ptr)
	{
		cleanup_mlx(mlx_data);
		return (exit_with_error("Failed to create MLX image"));
	}
	mlx_data->img_data = mlx_get_data_addr(mlx_data->img_ptr,
			&mlx_data->bits_per_pixel, &mlx_data->line_length,
			&mlx_data->endian);
	if (!mlx_data->img_data)
	{
		cleanup_mlx(mlx_data);
		return (exit_with_error("Failed to get image data address"));
	}
	return (0);
}

int	setup_mlx_hooks(t_mlx *mlx_data)
{
	mlx_hook(mlx_data->win_ptr, KeyPress, KeyPressMask, key_press_handler,
		mlx_data);
	mlx_hook(mlx_data->win_ptr, KeyRelease, KeyReleaseMask, key_release_handler,
		mlx_data);
	mlx_hook(mlx_data->win_ptr, DestroyNotify, StructureNotifyMask,
		close_window, mlx_data);
	mlx_loop_hook(mlx_data->mlx_ptr, game_loop, mlx_data);
	return (0);
}

void	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->m = 0;
	keys->escape = 0;
	keys->left = 0;
	keys->right = 0;
	keys->up = 0;
	keys->down = 0;
}

int	game_loop(t_mlx *mlx_data)
{
	handle_continuous_movement(mlx_data);
	clear_image(mlx_data);
	cast_rays(mlx_data, mlx_data->map_data);
	if (mlx_data->show_2d_map)
		render_2d_map(mlx_data);
	mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr,
		mlx_data->img_ptr, 0, 0);
	return (0);
}

int	init_mlx_window(t_mlx *mlx_data, t_map *map_data)
{
	mlx_data->map_data = map_data;
	mlx_data->show_2d_map = 0;
	init_keys(&mlx_data->keys);
	if (init_mlx_display(mlx_data) != 0)
		return (1);
	if (load_textures(mlx_data, &map_data->config) != 0)
	{
		cleanup_mlx(mlx_data);
		return (1);
	}
	if (setup_mlx_hooks(mlx_data) != 0)
		return (1);
	clear_image(mlx_data);
	cast_rays(mlx_data, mlx_data->map_data);
	mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr,
		mlx_data->img_ptr, 0, 0);
	return (0);
}
