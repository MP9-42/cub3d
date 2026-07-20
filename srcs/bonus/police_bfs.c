/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   police_bfs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 22:51:13 by alegeber          #+#    #+#             */
/*   Updated: 2026/07/20 23:29:20 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	bfs_alloc(t_bfs *bfs)
{
	bfs->visited = ft_calloc(bfs->total, sizeof(int));
	bfs->par_x = ft_calloc(bfs->total, sizeof(int));
	bfs->par_y = ft_calloc(bfs->total, sizeof(int));
	bfs->queue_x = ft_calloc(bfs->total, sizeof(int));
	bfs->queue_y = ft_calloc(bfs->total, sizeof(int));
}

void	bfs_init(int start_x, int start_y, t_bfs *bfs)
{
	bfs->front = 0;
	bfs->rear = 0;
	bfs->queue_x[bfs->rear] = start_x;
	bfs->queue_y[bfs->rear] = start_y;
	bfs->rear++;
	bfs->visited[start_y * bfs->width + start_x] = 1;
	bfs->dx[0] = 1;
	bfs->dy[0] = 0;
	bfs->dx[1] = -1;
	bfs->dy[1] = 0;
	bfs->dx[2] = 0;
	bfs->dy[2] = 1;
	bfs->dx[3] = 0;
	bfs->dy[3] = -1;
}

static void	algo_helper(t_map *map, t_bfs *bfs)
{
	while (bfs->i < 4)
	{
		bfs->nx = bfs->current_x + bfs->dx[bfs->i];
		bfs->ny = bfs->current_y + bfs->dy[bfs->i];
		if (bfs->ny >= 0 && bfs->ny < map->size && bfs->nx >= 0
			&& bfs->nx < bfs->width && map->rmap[bfs->ny][bfs->nx] != '1'
			&& !bfs->visited[bfs->ny * bfs->width + bfs->nx])
		{
			bfs->visited[bfs->ny * bfs->width + bfs->nx] = 1;
			bfs->par_x[bfs->ny * bfs->width + bfs->nx] = bfs->current_x;
			bfs->par_y[bfs->ny * bfs->width + bfs->nx] = bfs->current_y;
			bfs->queue_x[bfs->rear] = bfs->nx;
			bfs->queue_y[bfs->rear] = bfs->ny;
			bfs->rear++;
		}
		bfs->i++;
	}
}

void	breadth_first_search(t_map *map, t_bfs *bfs)
{
	while (bfs->front < bfs->rear)
	{
		bfs->current_x = bfs->queue_x[bfs->front];
		bfs->current_y = bfs->queue_y[bfs->front];
		bfs->front++;
		if (bfs->current_x == bfs->end_x && bfs->current_y == bfs->end_y)
			break ;
		bfs->i = 0;
		algo_helper(map, bfs);
	}
}
