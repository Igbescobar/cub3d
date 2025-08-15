/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:41:15 by igngonza          #+#    #+#             */
/*   Updated: 2024/04/23 17:44:06 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *need, size_t len)
{
	long unsigned int	i;
	long unsigned int	j;

	if (s == NULL && len == 0)
		return (NULL);
	i = 0;
	if (need[i] == '\0')
		return ((char *)s);
	while (s[i] && i < len)
	{
		j = 0;
		while (s[i + j] == need[j] && i + j < len)
		{
			j++;
			if (need[j] == '\0')
				return ((char *)&s[i]);
		}
		i++;
	}
	return (NULL);
}
