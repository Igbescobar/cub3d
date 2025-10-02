/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 00:00:00 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/30 21:28:45 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_ray(t_ray *ray, t_player *player, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

static void	calculate_step_and_side_dist(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

static void	perform_dda(t_ray *ray, t_map *map_data)
{
	while (ray->hit == 0)
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
		if (ray->map_x < 0 || ray->map_x >= map_data->map_width
			|| ray->map_y < 0 || ray->map_y >= map_data->map_height
			|| map_data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calculate_distance_and_height(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - player->pos_x + (1 - ray->step_x)
				/ 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->pos_y + (1 - ray->step_y)
				/ 2) / ray->dir_y;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

static int	get_texture_index(t_ray *ray)
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

static double	calculate_wall_x(t_ray *ray, t_player *player)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = player->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = player->pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

static int	get_texture_pixel(t_mlx *mlx, int tex_index, int tex_x, int tex_y)
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

static void	draw_textured_wall(t_mlx *mlx, int x, t_ray *ray, t_player *player)
{
	int		tex_index;
	int		tex_x;
	double	wall_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;
	int		y;

	tex_index = get_texture_index(ray);
	wall_x = calculate_wall_x(ray, player);
	tex_x = (int)(wall_x * (double)mlx->textures[tex_index].width);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = mlx->textures[tex_index].width - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = mlx->textures[tex_index].width - tex_x - 1;
	step = 1.0 * mlx->textures[tex_index].height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (mlx->textures[tex_index].height - 1);
		tex_pos += step;
		color = get_texture_pixel(mlx, tex_index, tex_x, tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel_to_image(mlx, x, y, color);
		y++;
	}
}

static void	draw_vertical_line(t_mlx *mlx, int x, t_ray *ray, t_map *map_data)
{
	int	y;
	int	floor_color;
	int	ceiling_color;

	floor_color = (map_data->config.floor_color[0] << 16) | (map_data->config.floor_color[1] << 8) | map_data->config.floor_color[2];
	ceiling_color = (map_data->config.ceiling_color[0] << 16) | (map_data->config.ceiling_color[1] << 8) | map_data->config.ceiling_color[2];
	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel_to_image(mlx, x, y, ceiling_color);
		y++;
	}
	draw_textured_wall(mlx, x, ray, &map_data->player);
	y = ray->draw_end + 1;
	while (y < WIN_HEIGHT)
	{
		put_pixel_to_image(mlx, x, y, floor_color);
		y++;
	}
}

void	cast_rays(t_mlx *mlx, t_map *map_data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&ray, &map_data->player, x);
		calculate_step_and_side_dist(&ray, &map_data->player);
		perform_dda(&ray, map_data);
		calculate_distance_and_height(&ray, &map_data->player);
		draw_vertical_line(mlx, x, &ray, map_data);
		x++;
	}
}
