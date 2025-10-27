/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:00:00 by igbescobar        #+#    #+#             */
/*   Updated: 2025/10/27 10:42:43 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_wall_collision(t_ray *ray, t_map *map_data)
{
	if (ray->map_x < 0 || ray->map_x >= map_data->map_width
		|| ray->map_y < 0 || ray->map_y >= map_data->map_height)
		return (1);
	if (map_data->map[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

static void	advance_ray_step(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	perform_dda(t_ray *ray, t_map *map_data)
{
	while (ray->hit == 0)
	{
		advance_ray_step(ray);
		if (check_wall_collision(ray, map_data))
			ray->hit = 1;
	}
}
