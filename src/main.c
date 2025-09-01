/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:57:19 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/01 11:22:20 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_map	map_data;
	t_mlx	mlx_data;

	if (parsing_handler(argc, argv, &map_data) != 0)
	{
		cleanup_get_next_line();
		return (1);
	}
	if (init_mlx_window(&mlx_data, &map_data) != 0)
	{
		free_map(&map_data);
		cleanup_get_next_line();
		return (1);
	}
	mlx_loop(mlx_data.mlx_ptr);
	cleanup_mlx(&mlx_data);
	free_map(&map_data);
	return (0);
}
