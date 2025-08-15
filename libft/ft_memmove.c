/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:22:35 by igngonza          #+#    #+#             */
/*   Updated: 2024/04/23 18:02:14 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	if (s == d)
		return (dest);
	else
	{
		if (s < d)
		{
			while (++i <= n)
				d[n - i] = s[n - i];
		}
		else
		{
			while (n--)
				*d++ = *s++;
		}
		return (dest);
	}
}
