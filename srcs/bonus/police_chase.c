/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   police_chase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 23:01:02 by alegeber          #+#    #+#             */
/*   Updated: 2026/07/20 23:29:24 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec * 0.000001);
}

static void	move_npc(t_cub *cub, double mx, double my)
{
	double	nx;
	double	ny;

	nx = cub->npc->pos_x + mx;
	ny = cub->npc->pos_y + my;
	if (!is_wall(cub->map, (int)nx, (int)cub->npc->pos_y))
		cub->npc->pos_x = nx;
	if (!is_wall(cub->map, (int)cub->npc->pos_x, (int)ny))
		cub->npc->pos_y = ny;
}

void	get_length(t_cub *cub, t_npc *npc, t_bfs *bfs, double now)
{
	if (now - cub->npc->last_path_time > NPC_RECOMPUTE)
	{
		npc->last_path_time = now;
		bfs->path_x = npc->path_x;
		bfs->path_y = npc->path_y;
		bfs->start_x = (int)npc->pos_x;
		bfs->start_y = (int)npc->pos_y;
		bfs->end_x = (int)cub->player->pos_x;
		bfs->end_y = (int)cub->player->pos_y;
		cub->npc->path_length = bifis(cub->map, &*bfs);
		cub->npc->current_target = 1;
	}
}

void	get_distance(t_cub *cub, t_npc *npc, t_bfs *bfs)
{
	bfs->target_x = cub->npc->path_x[cub->npc->current_target] + 0.5;
	bfs->target_y = cub->npc->path_y[cub->npc->current_target] + 0.5;
	npc->dx = bfs->target_x - cub->npc->pos_x;
	npc->dy = bfs->target_y - cub->npc->pos_y;
	bfs->dist = sqrt(npc->dx * npc->dx + npc->dy * npc->dy);
}

void	move_n_get_distance(t_cub *cub, t_npc *npc, t_bfs *bfs)
{
	npc->dx /= bfs->dist;
	npc->dy /= bfs->dist;
	move_npc(cub, npc->dx * cub->npc->speed, npc->dy * cub->npc->speed);
	npc->dx = cub->player->pos_x - cub->npc->pos_x;
	npc->dy = cub->player->pos_y - cub->npc->pos_y;
	bfs->dist = sqrt(npc->dx * npc->dx + npc->dy * npc->dy);
}
