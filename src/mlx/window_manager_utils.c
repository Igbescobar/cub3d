/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdurban- <fdurban-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:21:49 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/02 17:17:29 by fdurban-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_hook(int keycode, t_mlx *mlx_data)
{
	if (keycode == XK_Escape)
		close_window(mlx_data);
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
