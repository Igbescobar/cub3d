/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:50:00 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/01 16:31:10 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_texture_info(t_mlx *mlx_data)
{
	printf("=== TEXTURE LOADING SUCCESS ===\n");
	printf("North texture: %dx%d pixels\n",
		mlx_data->textures[TEXTURE_NORTH].width,
		mlx_data->textures[TEXTURE_NORTH].height);
	printf("South texture: %dx%d pixels\n",
		mlx_data->textures[TEXTURE_SOUTH].width,
		mlx_data->textures[TEXTURE_SOUTH].height);
	printf("West texture: %dx%d pixels\n",
		mlx_data->textures[TEXTURE_WEST].width,
		mlx_data->textures[TEXTURE_WEST].height);
	printf("East texture: %dx%d pixels\n",
		mlx_data->textures[TEXTURE_EAST].width,
		mlx_data->textures[TEXTURE_EAST].height);
	printf("Floor color: RGB(%d, %d, %d)\n",
		mlx_data->map_data->config.floor_color[0],
		mlx_data->map_data->config.floor_color[1],
		mlx_data->map_data->config.floor_color[2]);
	printf("Ceiling color: RGB(%d, %d, %d)\n",
		mlx_data->map_data->config.ceiling_color[0],
		mlx_data->map_data->config.ceiling_color[1],
		mlx_data->map_data->config.ceiling_color[2]);
}
