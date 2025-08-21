/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:10:50 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/20 13:12:59 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_valid_texture_path(char *path)
{
	int	len;
	int	fd;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len == 0)
		return (0);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (0);
	if (path[len - 1] == '/')
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}
