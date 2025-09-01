/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_direction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:27:22 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/01 13:34:44 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_north_direction(t_player *player)
{
	player->dir_x = 0.0;
	player->dir_y = -1.0;
	player->plane_x = 0.66;
	player->plane_y = 0.0;
}

void	set_south_direction(t_player *player)
{
	player->dir_x = 0.0;
	player->dir_y = 1.0;
	player->plane_x = -0.66;
	player->plane_y = 0.0;
}

void	set_east_direction(t_player *player)
{
	player->dir_x = 1.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.66;
}

void	set_west_direction(t_player *player)
{
	player->dir_x = -1.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = -0.66;
}
