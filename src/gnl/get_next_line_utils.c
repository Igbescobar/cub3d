/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:02:25 by igngonza          #+#    #+#             */
/*   Updated: 2025/08/15 14:02:59 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*ft_append(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		total_size;
	char	*solution;

	i = 0;
	j = 0;
	total_size = ft_strlen(s1) + ft_strlen(s2);
	solution = malloc(sizeof(char) * (total_size + 1));
	if (!solution || !s1 || !s2)
		return (NULL);
	while (s1[i])
	{
		solution[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		solution[i] = s2[j];
		i++;
		j++;
	}
	solution[total_size] = 0;
	return (solution);
}

char	*ft_strchr(const char *string, int searchedChar)
{
	char	*str;

	str = (char *)string;
	while (*str != searchedChar && *str != 0)
		str++;
	if (*str == searchedChar)
		return (str);
	else
		return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0x00;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char *result;

	result = malloc(count * size);
	if (!result)
		return (NULL);
	ft_bzero(result, count * size);
	return (result);
}