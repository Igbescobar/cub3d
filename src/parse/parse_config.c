/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:15:00 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/22 17:24:46 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_config_incomplete(t_config *config)
{
	if (!config->north_texture)
		return (exit_with_error("Missing North texture (NO)"));
	if (!config->south_texture)
		return (exit_with_error("Missing South texture (SO)"));
	if (!config->west_texture)
		return (exit_with_error("Missing West texture (WE)"));
	if (!config->east_texture)
		return (exit_with_error("Missing East texture (EA)"));
	if (config->floor_color[0] == -1 || config->floor_color[1] == -1
		|| config->floor_color[2] == -1)
		return (exit_with_error("Missing or invalid Floor color (F)"));
	if (config->ceiling_color[0] == -1 || config->ceiling_color[1] == -1
		|| config->ceiling_color[2] == -1)
		return (exit_with_error("Missing or invalid Ceiling color (C)"));
	return (0);
}

static int	cleanup_and_return_error(int fd, char *line, t_config *config)
{
	if (line)
		free(line);
	if (fd >= 0)
		close(fd);
	free_config(config);
	return (1);
}

static int	process_config_file(int fd, t_config *config)
{
	char	*line;
	int		map_started;
	int		map_ended;

	map_started = 0;
	map_ended = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (process_line(line, config, &map_started, &map_ended))
			return (cleanup_and_return_error(fd, line, config));
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_config_from_file(const char *filename, t_config *config)
{
	int	fd;

	init_config(config);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	if (process_config_file(fd, config))
		return (1);
	close(fd);
	if (is_config_incomplete(config))
	{
		free_config(config);
		return (1);
	}
	return (0);
}

int	parse_config_line(char *line, t_config *config)
{
	line = skip_whitespace(line);
	if (*line == '\0' || *line == '\n')
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture_line(line + 3, &config->north_texture));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture_line(line + 3, &config->south_texture));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture_line(line + 3, &config->west_texture));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture_line(line + 3, &config->east_texture));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color_line(line + 2, config->floor_color));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color_line(line + 2, config->ceiling_color));
	return (1);
}
