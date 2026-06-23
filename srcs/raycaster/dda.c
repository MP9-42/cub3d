/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:29:14 by alegeber          #+#    #+#             */
/*   Updated: 2026/06/23 11:12:02 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int is_wall(t_map *map, int x, int y)
{
	int	len;

	if (y < 0 || y >= map->size || x < 0)
		return 1;
	len = ft_strlen(map->rmap[y]);
	if (x >= len)
		return 1;
	return (map->rmap[y][x] == '1');
}

