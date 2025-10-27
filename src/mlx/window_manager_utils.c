/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:21:49 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/19 11:43:26 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_press_handler(int keycode, t_mlx *mlx_data)
{
	if (keycode == XK_Escape)
		mlx_data->keys.escape = 1;
	if (keycode == XK_w)
		mlx_data->keys.w = 1;
	if (keycode == XK_a)
		mlx_data->keys.a = 1;
	if (keycode == XK_s)
		mlx_data->keys.s = 1;
	if (keycode == XK_d)
		mlx_data->keys.d = 1;
	if (keycode == XK_m)
		mlx_data->keys.m = 1;
	if (keycode == XK_Left)
		mlx_data->keys.left = 1;
	if (keycode == XK_Right)
		mlx_data->keys.right = 1;
	if (keycode == XK_Up)
		mlx_data->keys.up = 1;
	if (keycode == XK_Down)
		mlx_data->keys.down = 1;
	return (0);
}

static void	toggle_2d_map(t_mlx *mlx_data)
{
	mlx_data->show_2d_map = !mlx_data->show_2d_map;
	if (mlx_data->show_2d_map)
		render_2d_map(mlx_data);
	else
	{
		clear_image(mlx_data);
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr,
			mlx_data->img_ptr, 0, 0);
	}
}

int	key_release_handler(int keycode, t_mlx *mlx_data)
{
	if (keycode == XK_Escape)
		close_window(mlx_data);
	if (keycode == XK_w)
		mlx_data->keys.w = 0;
	if (keycode == XK_a)
		mlx_data->keys.a = 0;
	if (keycode == XK_s)
		mlx_data->keys.s = 0;
	if (keycode == XK_d)
		mlx_data->keys.d = 0;
	if (keycode == XK_m)
		toggle_2d_map(mlx_data);
	if (keycode == XK_Left)
		mlx_data->keys.left = 0;
	if (keycode == XK_Right)
		mlx_data->keys.right = 0;
	if (keycode == XK_Up)
		mlx_data->keys.up = 0;
	if (keycode == XK_Down)
		mlx_data->keys.down = 0;
	return (0);
}

int	close_window(t_mlx *mlx_data)
{
	cleanup_mlx(mlx_data);
	if (mlx_data->map_data)
		free_map(mlx_data->map_data);
	cleanup_get_next_line();
	exit(0);
	return (0);
}

void	cleanup_mlx(t_mlx *mlx_data)
{
	cleanup_textures(mlx_data);
	if (mlx_data->img_ptr && mlx_data->mlx_ptr)
		mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->img_ptr);
	if (mlx_data->win_ptr && mlx_data->mlx_ptr)
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
	if (mlx_data->mlx_ptr)
	{
		mlx_destroy_display(mlx_data->mlx_ptr);
		free(mlx_data->mlx_ptr);
	}
}
