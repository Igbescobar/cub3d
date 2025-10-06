/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_calculation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igbescobar <igbescobar@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:00:00 by igbescobar        #+#    #+#             */
/*   Updated: 2025/10/06 12:26:49 by igbescobar       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	calculate_perpendicular_distance(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - player->pos_x + (1 - ray->step_x)
				/ 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->pos_y + (1 - ray->step_y)
				/ 2) / ray->dir_y;
}

static void	calculate_wall_height_and_bounds(t_ray *ray)
{
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	calculate_distance_and_height(t_ray *ray, t_player *player)
{
	calculate_perpendicular_distance(ray, player);
	calculate_wall_height_and_bounds(ray);
}

double	calculate_wall_x(t_ray *ray, t_player *player)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = player->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = player->pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}