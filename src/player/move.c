/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:59:13 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/19 11:29:29 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_forward(t_mlx *mlx_data)
{
	t_player	*player;
	double		move_x;
	double		move_y;

	player = &mlx_data->map_data->player;
	move_x = player->dir_x * MOVE_SPEED;
	move_y = player->dir_y * MOVE_SPEED;
	move_player(mlx_data, move_x, move_y);
}

void	move_backward(t_mlx *mlx_data)
{
	t_player	*player;
	double		move_x;
	double		move_y;

	player = &mlx_data->map_data->player;
	move_x = -player->dir_x * MOVE_SPEED;
	move_y = -player->dir_y * MOVE_SPEED;
	move_player(mlx_data, move_x, move_y);
}

void	strafe_left(t_mlx *mlx_data)
{
	t_player	*player;
	double		move_x;
	double		move_y;

	player = &mlx_data->map_data->player;
	move_x = player->dir_y * MOVE_SPEED;
	move_y = -player->dir_x * MOVE_SPEED;
	move_player(mlx_data, move_x, move_y);
}

void	strafe_right(t_mlx *mlx_data)
{
	t_player	*player;
	double		move_x;
	double		move_y;

	player = &mlx_data->map_data->player;
	move_x = -player->dir_y * MOVE_SPEED;
	move_y = player->dir_x * MOVE_SPEED;
	move_player(mlx_data, move_x, move_y);
}
