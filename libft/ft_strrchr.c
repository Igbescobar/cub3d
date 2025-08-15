/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:29:08 by igngonza          #+#    #+#             */
/*   Updated: 2024/04/23 17:44:13 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*source;

	source = NULL;
	while (*s)
	{
		if (*s == (char)c)
			source = s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return ((char *)source);
}
