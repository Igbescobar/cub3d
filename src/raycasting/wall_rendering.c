/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:00:00 by igbescobar        #+#    #+#             */
/*   Updated: 2025/10/27 11:14:47 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	apply_wall_shading(int color, t_ray *ray)
{
	if (ray->side == 1)
		color = (color >> 1) & 8355711;
	return (color);
}

static void	draw_ceiling(t_mlx *mlx, int x, int draw_start, int ceiling_color)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		put_pixel_to_image(mlx, x, y, ceiling_color);
		y++;
	}
}

static void	draw_floor(t_mlx *mlx, int x, int draw_end, int floor_color)
{
	int	y;

	y = draw_end + 1;
	while (y < WIN_HEIGHT)
	{
		put_pixel_to_image(mlx, x, y, floor_color);
		y++;
	}
}

void	draw_textured_wall(t_mlx *mlx, int x, t_ray *ray, t_player *player)
{
	int		tex_index;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;

	tex_index = get_texture_index(ray);
	tex_x = calculate_texture_x(mlx, ray, calculate_wall_x(ray, player),
			tex_index);
	step = 1.0 * mlx->textures[tex_index].height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		put_pixel_to_image(mlx, x, y, apply_wall_shading(get_texture_pixel(mlx,
					tex_index, tex_x,
					(int)tex_pos & (mlx->textures[tex_index].height - 1)),
				ray));
		tex_pos += step;
		y++;
	}
}

void	draw_vertical_line(t_mlx *mlx, int x, t_ray *ray, t_map *map_data)
{
	int	floor_color;
	int	ceiling_color;

	floor_color = create_rgb_color(map_data->config.floor_color[0],
			map_data->config.floor_color[1], map_data->config.floor_color[2]);
	ceiling_color = create_rgb_color(map_data->config.ceiling_color[0],
			map_data->config.ceiling_color[1],
			map_data->config.ceiling_color[2]);
	draw_ceiling(mlx, x, ray->draw_start, ceiling_color);
	draw_textured_wall(mlx, x, ray, &map_data->player);
	draw_floor(mlx, x, ray->draw_end, floor_color);
}
