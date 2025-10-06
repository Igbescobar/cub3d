/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igbescobar <igbescobar@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:00:00 by igbescobar        #+#    #+#             */
/*   Updated: 2025/10/06 12:26:49 by igbescobar       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_texture_index(t_ray *ray)
{
	if (ray->side == 1)
	{
		if (ray->step_y == 1)
			return (TEXTURE_SOUTH);
		else
			return (TEXTURE_NORTH);
	}
	else
	{
		if (ray->step_x == 1)
			return (TEXTURE_EAST);
		else
			return (TEXTURE_WEST);
	}
}

int	get_texture_pixel(t_mlx *mlx, int tex_index, int tex_x, int tex_y)
{
	t_texture	*texture;
	char		*pixel;
	int			color;

	texture = &mlx->textures[tex_index];
	if (tex_x < 0 || tex_x >= texture->width || tex_y < 0
		|| tex_y >= texture->height)
		return (0);
	pixel = texture->img_data + (tex_y * texture->line_length + tex_x
			* (texture->bits_per_pixel / 8));
	color = *(int *)pixel;
	return (color);
}

int	calculate_texture_x(t_mlx *mlx, t_ray *ray, double wall_x, int tex_index)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)mlx->textures[tex_index].width);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = mlx->textures[tex_index].width - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = mlx->textures[tex_index].width - tex_x - 1;
	return (tex_x);
}