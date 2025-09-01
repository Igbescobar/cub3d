/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:30:00 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/01 13:27:42 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	find_player_position(t_map *map_data, int *x, int *y, char *orientation)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_data->map_height)
	{
		j = 0;
		while (j < (int)ft_strlen(map_data->map[i]))
		{
			if (is_player_position(map_data->map[i][j]))
			{
				*x = j;
				*y = i;
				*orientation = map_data->map[i][j];
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	set_player_direction(t_player *player, char orientation)
{
	if (orientation == 'N')
		set_north_direction(player);
	else if (orientation == 'S')
		set_south_direction(player);
	else if (orientation == 'E')
		set_east_direction(player);
	else if (orientation == 'W')
		set_west_direction(player);
}

int	init_player(t_map *map_data)
{
	int		player_x;
	int		player_y;
	char	orientation;

	if (find_player_position(map_data, &player_x, &player_y, &orientation))
		return (exit_with_error("No player position found in map"));
	map_data->player.pos_x = (double)player_x + 0.5;
	map_data->player.pos_y = (double)player_y + 0.5;
	set_player_direction(&map_data->player, orientation);
	return (0);
}
