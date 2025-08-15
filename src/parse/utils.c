/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:20:03 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/15 13:30:21 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	has_cub_extension(const char *filename)
{
	const char	*dot = ft_strrchr(filename, '.');

	if (!dot || dot == filename)
		return (0);
	return (ft_strncmp(dot, ".cub", 4) == 0);
}
