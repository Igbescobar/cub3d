/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:20:00 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/15 18:21:04 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	point_hits_wall(t_mlx *mlx_data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= mlx_data->map_data->map_width || map_y < 0
		|| map_y >= mlx_data->map_data->map_height)
		return (1);
	if (map_x >= (int)ft_strlen(mlx_data->map_data->map[map_y]))
		return (1);
	return (mlx_data->map_data->map[map_y][map_x] == '1');
}

int	is_valid_position(t_mlx *mlx_data, double new_x, double new_y)
{
	double		radius;
	t_player	*player;

	radius = 0.15;
	if (point_hits_wall(mlx_data, new_x - radius, new_y)
		|| point_hits_wall(mlx_data, new_x + radius, new_y)
		|| point_hits_wall(mlx_data, new_x, new_y - radius)
		|| point_hits_wall(mlx_data, new_x, new_y + radius)
		|| point_hits_wall(mlx_data, new_x - radius, new_y - radius)
		|| point_hits_wall(mlx_data, new_x + radius, new_y - radius)
		|| point_hits_wall(mlx_data, new_x - radius, new_y + radius)
		|| point_hits_wall(mlx_data, new_x + radius, new_y + radius))
		return (0);
	player = &mlx_data->map_data->player;
	if (point_hits_wall(mlx_data, new_x + player->dir_x * 0.3, new_y
			+ player->dir_y * 0.3))
		return (0);
	return (1);
}

static void	get_movement_direction(int keycode, t_player *player,
		double *delta_x, double *delta_y)
{
	if (keycode == KEY_W)
	{
		*delta_x = player->dir_x * MOVE_SPEED;
		*delta_y = player->dir_y * MOVE_SPEED;
	}
	else if (keycode == KEY_S)
	{
		*delta_x = -player->dir_x * MOVE_SPEED;
		*delta_y = -player->dir_y * MOVE_SPEED;
	}
	else if (keycode == KEY_A)
	{
		*delta_x = player->dir_y * MOVE_SPEED;
		*delta_y = -player->dir_x * MOVE_SPEED;
	}
	else if (keycode == KEY_D)
	{
		*delta_x = -player->dir_y * MOVE_SPEED;
		*delta_y = player->dir_x * MOVE_SPEED;
	}
	else
	{
		*delta_x = 0;
		*delta_y = 0;
	}
}

static void	move_player(t_mlx *mlx_data, double delta_x, double delta_y)
{
	t_player	*player;
	double		step_x;
	double		step_y;
	int			i;

	player = &mlx_data->map_data->player;
	step_x = delta_x / 10;
	step_y = delta_y / 10;
	i = 0;
	while (i < 10)
	{
		if (is_valid_position(mlx_data, player->pos_x + step_x, player->pos_y
				+ step_y))
		{
			player->pos_x += step_x;
			player->pos_y += step_y;
		}
		else
			break ;
		i++;
	}
}

void	handle_movement_keys(int keycode, t_mlx *mlx_data)
{
	double	delta_x;
	double	delta_y;

	get_movement_direction(keycode, &mlx_data->map_data->player, &delta_x,
		&delta_y);
	if (delta_x == 0 && delta_y == 0)
		return ;
	move_player(mlx_data, delta_x, delta_y);
	render_2d_map(mlx_data);
}
