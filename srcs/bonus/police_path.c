/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   police_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 22:49:00 by alegeber          #+#    #+#             */
/*   Updated: 2026/08/12 16:31:52 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_bfs(t_bfs *bfs)
{
	free(bfs->visited);
	free(bfs->par_x);
	free(bfs->par_y);
	free(bfs->queue_x);
	free(bfs->queue_y);
}

static void	path_reconstructor(t_bfs *bfs)
{
	bfs->len = 0;
	bfs->current_x = bfs->end_x;
	bfs->current_y = bfs->end_y;
	while (bfs->current_x != bfs->start_x || bfs->current_y != bfs->start_y)
	{
		if (bfs->len >= MAX_PATH - 1)
			break ;
		bfs->path_x[bfs->len] = bfs->current_x;
		bfs->path_y[bfs->len] = bfs->current_y;
		bfs->len++;
		bfs->idx = bfs->current_y * bfs->width + bfs->current_x;
		bfs->nx = bfs->par_x[bfs->idx];
		bfs->ny = bfs->par_y[bfs->idx];
		bfs->current_x = bfs->nx;
		bfs->current_y = bfs->ny;
	}
}

static void	path_swapper(t_bfs *bfs)
{
	bfs->path_x[bfs->len] = bfs->current_x;
	bfs->path_y[bfs->len] = bfs->current_y;
	bfs->len++;
	bfs->i = 0;
	while (bfs->i < bfs->len / 2)
	{
		bfs->nx = bfs->path_x[bfs->i];
		bfs->ny = bfs->path_y[bfs->i];
		bfs->path_x[bfs->i] = bfs->path_x[bfs->len - 1 - bfs->i];
		bfs->path_y[bfs->i] = bfs->path_y[bfs->len - 1 - bfs->i];
		bfs->path_x[bfs->len - 1 - bfs->i] = bfs->nx;
		bfs->path_y[bfs->len - 1 - bfs->i] = bfs->ny;
		bfs->i++;
	}
}

// Performs a breadth first search starting from the initial
// position until the destination is found or no more tiles
// are left to explore.
int	bifis(t_map *map, t_bfs *bfs)
{
	int	len;

	bfs->width = map->max_width;
	bfs->total = map->size * bfs->width;
	bfs_alloc(bfs);
	if (!bfs->visited || !bfs->par_x || !bfs->par_y
		|| !bfs->queue_x || !bfs->queue_y)
		return (free(bfs->visited), free(bfs->par_x), free(bfs->par_y),
			free(bfs->queue_x), free(bfs->queue_y), 0);
	bfs_init(bfs->start_x, bfs->start_y, bfs);
	breadth_first_search(map, bfs);
	if (!bfs->visited[bfs->end_y * bfs->width + bfs->end_x])
		return (free(bfs->visited), free(bfs->par_x), free(bfs->par_y),
			free(bfs->queue_x), free(bfs->queue_y), 0);
	path_reconstructor(bfs);
	if (bfs->current_x != bfs->start_x || bfs->current_y != bfs->start_y)
		return (free(bfs->visited), free(bfs->par_x), free(bfs->par_y),
			free(bfs->queue_x), free(bfs->queue_y), 0);
	path_swapper(bfs);
	len = bfs->len;
	free_bfs(bfs);
	return (len);
}
