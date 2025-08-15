/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:36:45 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/15 13:40:52 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parsing_handler(int argc, char **argv)
{
	if (argc != 2)
		return (exit_with_error("Usage: ./cub3d <map_file.cub>"));

	if (!has_cub_extension(argv[1]))
		return (exit_with_error("Invalid file extension. Expected a .cub file."));

	if (access(argv[1], R_OK) != 0)
		return (exit_with_error("Cannot access map file."));

	return (0);
}