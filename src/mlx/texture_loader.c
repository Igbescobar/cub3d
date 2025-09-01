/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:40:00 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/01 16:30:06 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	validate_texture_files(t_config *config)
{
	if (!is_valid_texture_path(config->north_texture))
		return (exit_with_error("Invalid north texture path"));
	if (!is_valid_texture_path(config->south_texture))
		return (exit_with_error("Invalid south texture path"));
	if (!is_valid_texture_path(config->west_texture))
		return (exit_with_error("Invalid west texture path"));
	if (!is_valid_texture_path(config->east_texture))
		return (exit_with_error("Invalid east texture path"));
	return (0);
}

int	load_single_texture(t_mlx *mlx_data, t_texture *texture, char *path)
{
	texture->img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr, path,
			&texture->width, &texture->height);
	if (!texture->img_ptr)
		return (exit_with_error("Failed to load texture image"));
	texture->img_data = mlx_get_data_addr(texture->img_ptr,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (!texture->img_data)
	{
		mlx_destroy_image(mlx_data->mlx_ptr, texture->img_ptr);
		return (exit_with_error("Failed to get texture data address"));
	}
	return (0);
}

void	cleanup_textures(t_mlx *mlx_data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (mlx_data->textures[i].img_ptr && mlx_data->mlx_ptr)
			mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->textures[i].img_ptr);
		i++;
	}
}

int	load_textures(t_mlx *mlx_data, t_config *config)
{
	if (validate_texture_files(config) != 0)
		return (1);
	if (load_single_texture(mlx_data, &mlx_data->textures[TEXTURE_NORTH],
			config->north_texture) != 0)
		return (1);
	if (load_single_texture(mlx_data, &mlx_data->textures[TEXTURE_SOUTH],
			config->south_texture) != 0)
		return (1);
	if (load_single_texture(mlx_data, &mlx_data->textures[TEXTURE_WEST],
			config->west_texture) != 0)
		return (1);
	if (load_single_texture(mlx_data, &mlx_data->textures[TEXTURE_EAST],
			config->east_texture) != 0)
		return (1);
	return (0);
}
