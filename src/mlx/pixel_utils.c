/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:00:00 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/19 12:10:54 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	put_pixel_to_image(t_mlx *mlx_data, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	offset = (y * mlx_data->line_length) + (x * (mlx_data->bits_per_pixel / 8));
	pixel = mlx_data->img_data + offset;
	*(int *)pixel = color;
}

int	create_rgb_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	draw_rectangle(t_mlx *mlx_data, t_rect rect, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < rect.height)
	{
		j = 0;
		while (j < rect.width)
		{
			put_pixel_to_image(mlx_data, rect.x + j, rect.y + i, color);
			j++;
		}
		i++;
	}
}

void	clear_image(t_mlx *mlx_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel_to_image(mlx_data, x, y, 0x000000);
			x++;
		}
		y++;
	}
}
