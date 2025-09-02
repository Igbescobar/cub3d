/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdurban- <fdurban-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:00:00 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/02 16:28:46 by fdurban-         ###   ########.fr       */
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
	mlx_key_hook(mlx_data->win_ptr, key_hook, mlx_data);
	mlx_hook(mlx_data->win_ptr, 17, 0, close_window, mlx_data);
	return (0);
}

int	init_mlx_window(t_mlx *mlx_data, t_map *map_data)
{
	mlx_data->map_data = map_data;
	if (init_mlx_display(mlx_data) != 0)
		return (1);
	if (setup_mlx_hooks(mlx_data) != 0)
		return (1);
	return (0);
}
