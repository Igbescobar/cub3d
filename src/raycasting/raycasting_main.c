/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igbescobar <igbescobar@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:00:00 by igbescobar        #+#    #+#             */
/*   Updated: 2025/10/06 12:26:50 by igbescobar       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	cast_single_ray(t_mlx *mlx, t_map *map_data, int x)
{
	t_ray	ray;

	init_ray(&ray, &map_data->player, x);
	calculate_step_and_side_dist(&ray, &map_data->player);
	perform_dda(&ray, map_data);
	calculate_distance_and_height(&ray, &map_data->player);
	draw_vertical_line(mlx, x, &ray, map_data);
}

void	cast_rays(t_mlx *mlx, t_map *map_data)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_single_ray(mlx, map_data, x);
		x++;
	}
}