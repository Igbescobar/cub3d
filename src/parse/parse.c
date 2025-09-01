/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:36:45 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/01 11:58:31 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	run_all_validations(t_map *map_data)
{
	if (validate_map_characters(map_data) != 0)
		return (1);
	if (validate_enclosure(map_data) != 0)
		return (1);
	if (validate_player(map_data) != 0)
		return (1);
	if (init_player(map_data) != 0)
		return (1);
	return (0);
}

int	parsing_handler(int argc, char **argv, t_map *map_data)
{
	if (validate_argument_count(argc) != 0)
		return (1);
	if (validate_file_extension(argv[1]) != 0)
		return (1);
	if (validate_file_access(argv[1]) != 0)
		return (1);
	if (load_map_from_file(argv[1], map_data) != 0)
		return (1);
	if (run_all_validations(map_data) != 0)
		return (1);
	print_success_message(map_data);
	return (0);
}
