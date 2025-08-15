/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:17:04 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/15 14:03:25 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "libft.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>

// ========== Error Handling ==========
int			exit_with_error(const char *message);

// ========== Argument Parsing ==========
int			parsing_handler(int argc, char **argv);
int			has_cub_extension(const char *filename);

// ========== Map Struct ==========

typedef struct s_map
{
	char	**map;
	int		map_height;
}			t_map;

#endif
