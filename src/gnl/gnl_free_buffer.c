/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_free_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igngonza <igngonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:17:35 by igngonza          #+#    #+#             */
/*   Updated: 2025/09/01 13:22:38 by igngonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

void	cleanup_get_next_line(void)
{
	get_next_line(-1);
}
