/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igbescobar <igbescobar@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:00:00 by igbescobar        #+#    #+#             */
/*   Updated: 2025/10/06 12:26:50 by igbescobar       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	create_rgb_from_config(int color_array[3])
{
	return ((color_array[0] << 16) | (color_array[1] << 8) | color_array[2]);
}

int	clamp_texture_coordinate(int coord, int max_val)
{
	if (coord < 0)
		return (0);
	if (coord >= max_val)
		return (max_val - 1);
	return (coord);
}

int	validate_ray_direction(t_ray *ray)
{
	if (ray->dir_x == 0.0 && ray->dir_y == 0.0)
		return (0);
	if (ray->delta_dist_x < 0 || ray->delta_dist_y < 0)
		return (0);
	return (1);
}

double	calculate_camera_x(int x)
{
	return (2 * x / (double)WIN_WIDTH - 1);
}