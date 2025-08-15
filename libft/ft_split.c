/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:54:56 by igngonza          #+#    #+#             */
/*   Updated: 2024/04/23 18:02:11 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_find_total_tokens(const char *s, char c)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		if (*s != c)
		{
			++ret;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (ret);
}

static char	**ft_memory_allocation(const char *s, char c)
{
	char	**ret;

	ret = malloc(sizeof(char *) * (ft_find_total_tokens(s, c) + 1));
	if (!ret)
	{
		free(ret);
		ret = NULL;
	}
	return (ret);
}

static char	**ft_free_memory(char **ret)
{
	int	j;

	j = 0;
	while (ret[j])
	{
		free(ret[j]);
		j++;
	}
	free(ret);
	return (NULL);
}

char	**ft_copy_into_array(const char *s, char **ret, char c)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (*s && ret)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			ret[i] = ft_substr(s - len, 0, len);
			if (!ret[i])
				ret = ft_free_memory(ret);
			i++;
		}
		else
			++s;
	}
	if (ret != NULL)
		ret[i] = NULL;
	return (ret);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;

	if (!s)
		return (NULL);
	ret = ft_memory_allocation(s, c);
	ret = ft_copy_into_array(s, ret, c);
	return (ret);
}
