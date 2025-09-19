/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:08:51 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/19 12:38:42 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	handle_movement_keys(t_mlx *mlx_data)
{
	int	moved;

	moved = 0;
	if (mlx_data->keys.w)
		moved = (move_forward(mlx_data), 1);
	if (mlx_data->keys.s)
		moved = (move_backward(mlx_data), 1);
	if (mlx_data->keys.a)
		moved = (strafe_left(mlx_data), 1);
	if (mlx_data->keys.d)
		moved = (strafe_right(mlx_data), 1);
	return (moved);
}

static int	handle_rotation_keys(t_mlx *mlx_data)
{
	int	moved;

	moved = 0;
	if (mlx_data->keys.left)
		moved = (rotate_player(&mlx_data->map_data->player, -ROTATION_SPEED),
				1);
	if (mlx_data->keys.right)
		moved = (rotate_player(&mlx_data->map_data->player, ROTATION_SPEED), 1);
	return (moved);
}

int	handle_continuous_movement(t_mlx *mlx_data)
{
	int	movement_occurred;
	int	rotation_occurred;
	int	moved;

	movement_occurred = handle_movement_keys(mlx_data);
	rotation_occurred = handle_rotation_keys(mlx_data);
	moved = movement_occurred || rotation_occurred;
	if (moved && mlx_data->show_2d_map)
		render_2d_map(mlx_data);
	return (0);
}
