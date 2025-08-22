/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:10:10 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/22 17:43:51 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_color_value(char *str, int *index)
{
	int	value;

	if (!ft_isdigit(str[*index]))
		return (-1);
	value = ft_atoi(str + *index);
	while (str[*index] && ft_isdigit(str[*index]))
		(*index)++;
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

int	parse_rgb_colors(char *line, int colors[3])
{
	int	i;
	int	color_index;

	i = 0;
	color_index = 0;
	line = skip_whitespace(line);
	while (*line && color_index < 3)
	{
		colors[color_index] = parse_color_value(line, &i);
		if (colors[color_index] == -1)
			return (exit_with_error("Invalid RGB value in color \
        specification"));
		color_index++;
		line += i;
		if (*line == ',')
			line++;
		line = skip_whitespace(line);
		i = 0;
	}
	if (color_index != 3)
		return (exit_with_error("Incomplete RGB color specification"));
	return (0);
}

int	parse_texture_line(char *line, char **texture_ptr)
{
	char	*path;

	if (*texture_ptr != NULL)
		return (exit_with_error("Duplicate texture specification found"));
	path = extract_path(line);
	if (!path)
		return (exit_with_error("Could not extract texture path from line"));
	if (!is_valid_texture_path(path))
	{
		free(path);
		return (exit_with_error("Invalid texture file"));
	}
	*texture_ptr = path;
	return (0);
}

int	parse_color_line(char *line, int color[3])
{
	if (color[0] != -1)
		return (exit_with_error("Duplicate color specification found"));
	return (parse_rgb_colors(line, color));
}
