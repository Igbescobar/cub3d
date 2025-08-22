/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:40:16 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/22 17:16:12 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	handle_post_map_line(char *line, int *map_ended)
{
	char	*trimmed;

	trimmed = skip_whitespace(line);
	if (*trimmed != '\0' && *trimmed != '\n')
		return (1);
	*map_ended = 1;
	return (0);
}

static int	handle_config_line(char *line, t_config *config)
{
	int	success;

	success = parse_config_line(line, config);
	if (success && ft_strlen(skip_whitespace(line)) > 0)
		return (1);
	return (0);
}

static int	handle_map_line_start(t_config *config)
{
	if (is_config_incomplete(config))
	{
		printf("Error: Map found before all required \
      configuration is complete\n");
		return (1);
	}
	return (0);
}

int	is_map_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	line = skip_whitespace(line);
	if (!*line || *line == '\n')
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (0);
	i = 0;
	while (line[i])
	{
		if (!is_valid_map_character(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	process_line(char *line, t_config *config, int *map_started, int *map_ended)
{
	if (is_map_line(line))
	{
		if (!*map_started)
		{
			*map_started = 1;
			return (handle_map_line_start(config));
		}
		else if (*map_ended)
		{
			printf("Error: Invalid content found after map\n");
			printf("Map must be at the end of the file with \
        no content after it\n");
			return (1);
		}
	}
	else if (!*map_started)
		return (handle_config_line(line, config));
	else
		return (handle_post_map_line(line, map_ended));
	return (0);
}
