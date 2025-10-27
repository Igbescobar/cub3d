/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:20:00 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/19 12:33:50 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_wall(t_mlx *mlx_data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= mlx_data->map_data->map_width || map_y < 0
		|| map_y >= mlx_data->map_data->map_height)
		return (1);
	return (mlx_data->map_data->map[map_y][map_x] == '1');
}

static int	can_move_to(t_mlx *mlx_data, double new_x, double new_y)
{
	double	player_collision_radius;

	player_collision_radius = 0.3;
	if (is_wall(mlx_data, new_x - player_collision_radius, new_y
			- player_collision_radius))
		return (0);
	if (is_wall(mlx_data, new_x + player_collision_radius, new_y
			- player_collision_radius))
		return (0);
	if (is_wall(mlx_data, new_x - player_collision_radius, new_y
			+ player_collision_radius))
		return (0);
	if (is_wall(mlx_data, new_x + player_collision_radius, new_y
			+ player_collision_radius))
		return (0);
	return (1);
}

void	move_player(t_mlx *mlx_data, double move_x, double move_y)
{
	t_player	*player;
	double		new_x;
	double		new_y;

	player = &mlx_data->map_data->player;
	new_x = player->pos_x + move_x;
	new_y = player->pos_y + move_y;
	if (can_move_to(mlx_data, new_x, new_y))
	{
		player->pos_x = new_x;
		player->pos_y = new_y;
		return ;
	}
	if (can_move_to(mlx_data, new_x, player->pos_y))
	{
		player->pos_x = new_x;
		return ;
	}
	if (can_move_to(mlx_data, player->pos_x, new_y))
	{
		player->pos_y = new_y;
		return ;
	}
}

void	rotate_player(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_angle;
	double	sin_angle;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	player->dir_x = player->dir_x * cos_angle - player->dir_y * sin_angle;
	player->dir_y = old_dir_x * sin_angle + player->dir_y * cos_angle;
	player->plane_x = player->plane_x * cos_angle - player->plane_y * sin_angle;
	player->plane_y = old_plane_x * sin_angle + player->plane_y * cos_angle;
}
