/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   police_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 22:43:14 by alegeber          #+#    #+#             */
/*   Updated: 2026/07/20 23:29:27 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	assign_npc_stats(t_map *map, t_npc *npc, int y, int x)
{
	npc->pos_x = x + 0.5;
	npc->pos_y = y + 0.5;
	npc->speed = NPC_SPEED;
	npc->active = true;
	npc->path_length = 0;
	npc->current_target = 0;
	npc->last_path_time = 0;
	map->rmap[y][x] = '0';
}

t_npc	*init_npc(t_map *map)
{
	t_npc	*npc;
	int		y;
	int		x;

	y = 0;
	while (y < map->size)
	{
		x = 0;
		while (map->rmap[y][x])
		{
			if (map->rmap[y][x] == '6')
			{
				npc = ft_calloc(sizeof(t_npc), 1);
				if (!npc)
					return (NULL);
				assign_npc_stats(map, npc, y, x);
				return (npc);
			}
			x++;
		}
		y++;
	}
	return (NULL);
}
