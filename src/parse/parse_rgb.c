/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:10:10 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/20 13:11:49 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_color_value(char *str, int *index)
{
	int	value;
	int	i;
	int	is_negative;

	value = 0;
	i = *index;
	is_negative = 0;
	if (str[i] == '-')
	{
		is_negative = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	if (!str[i] || str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		value = value * 10 + (str[i] - '0');
		i++;
	}
	*index = i;
	if (is_negative)
		value = -value;
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
			return (1);
		color_index++;
		line += i;
		if (*line == ',')
			line++;
		line = skip_whitespace(line);
		i = 0;
	}
	return (color_index != 3);
}

int	parse_texture_line(char *line, char **texture_ptr)
{
	char	*path;

	if (*texture_ptr != NULL)
		return (1);
	path = extract_path(line);
	if (!path)
		return (1);
	if (!is_valid_texture_path(path))
	{
		free(path);
		return (1);
	}
	*texture_ptr = path;
	return (0);
}

int	parse_color_line(char *line, int color[3])
{
	if (color[0] != -1)
		return (1);
	return (parse_rgb_colors(line, color));
}
