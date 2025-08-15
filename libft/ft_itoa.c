/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ :+         +:+     */
/*   By: igngonza <igngonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:04:53 by igngonza          #+#    #+#             */
/*   Updated: 2024/03/27 10:59:45 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size_number(int n)
{
	int		size;
	long	number;

	number = n;
	size = 1;
	if (number < 0)
	{
		size++;
		number *= -1;
	}
	while (number >= 10)
	{
		size++;
		number = number / 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	number;
	char	*result;
	int		i;

	i = 0;
	result = (char *)malloc(ft_size_number(n) + 1 * (sizeof(char)));
	if (!result)
		return (NULL);
	if (n < 0)
		result[i] = '-';
	number = n;
	if (number < 0)
		number = -number;
	result[ft_size_number(n)] = '\0';
	i++;
	while (number >= 10)
	{
		result[ft_size_number(n) - i] = (number % 10) + 48;
		number = number / 10;
		i++;
	}
	result[ft_size_number(n) - i] = (number % 10) + 48;
	return (result);
}
