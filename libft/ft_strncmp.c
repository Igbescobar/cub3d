/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:46:42 by igngonza          #+#    #+#             */
/*   Updated: 2024/04/23 17:43:56 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*source1;
	const unsigned char	*source2;

	i = 0;
	source1 = (unsigned char *)s1;
	source2 = (unsigned char *)s2;
	while ((source1[i] || source2[i]) && i < n)
	{
		if (source1[i] != source2[i])
			return ((source1[i] - source2[i]));
		i++;
	}
	return (0);
}
