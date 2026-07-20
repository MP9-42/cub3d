/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   police.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 18:59:12 by MP9               #+#    #+#             */
/*   Updated: 2026/07/20 22:48:15 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <sys/time.h>

static double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec * 0.000001);
}

static void bfs_init(int start_x, int start_y, t_bfs *bfs)
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

static void bfs_alloc(t_bfs *bfs)
{
	bfs->visited = ft_calloc(bfs->total, sizeof(int));
	bfs->par_x = ft_calloc(bfs->total, sizeof(int));
	bfs->par_y = ft_calloc(bfs->total, sizeof(int));
	bfs->queue_x = ft_calloc(bfs->total, sizeof(int));
	bfs->queue_y = ft_calloc(bfs->total, sizeof(int));
}

static void algo_helper(t_map *map, t_bfs *bfs)
{
	while (bfs->i < 4)
	{
		bfs->nx = bfs->current_x + bfs->dx[bfs->i];
		bfs->ny = bfs->current_y + bfs->dy[bfs->i];
		if (bfs->ny >= 0 && bfs->ny < map->size && bfs->nx >= 0 && bfs->nx < bfs->width
		    && map->rmap[bfs->ny][bfs->nx] != '1'
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

static void path_reconstructor(t_bfs *bfs)
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

static void path_swapper(t_bfs *bfs)
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

static void breadth_first_search(t_map *map, t_bfs *bfs)
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

static void free_bfs(t_bfs *bfs)
{
	free(bfs->visited);
	free(bfs->par_x);
	free(bfs->par_y);
	free(bfs->queue_x);
	free(bfs->queue_y);
}

static int	bifis(t_map *map, t_bfs *bfs)
{
	int len;

	bfs->width = map->max_width;
	bfs->total = map->size * bfs->width;
	bfs_alloc(bfs);
	if (!bfs->visited || !bfs->par_x || !bfs->par_y || !bfs->queue_x || !bfs->queue_y)
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

void get_length(t_cub *cub, t_npc *npc, t_bfs *bfs, double now)
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

void get_distance(t_cub *cub, t_npc *npc, t_bfs *bfs)
{
	bfs->target_x = cub->npc->path_x[cub->npc->current_target] + 0.5;
	bfs->target_y = cub->npc->path_y[cub->npc->current_target] + 0.5;
	npc->dx = bfs->target_x - cub->npc->pos_x;
	npc->dy = bfs->target_y - cub->npc->pos_y;
	bfs->dist = sqrt(npc->dx * npc->dx + npc->dy * npc->dy);
}

void move_n_get_distance(t_cub *cub, t_npc *npc, t_bfs *bfs)
{
	npc->dx /= bfs->dist;
	npc->dy /= bfs->dist;
	move_npc(cub, npc->dx * cub->npc->speed, npc->dy * cub->npc->speed);
	npc->dx = cub->player->pos_x - cub->npc->pos_x;
	npc->dy = cub->player->pos_y - cub->npc->pos_y;
	bfs->dist = sqrt(npc->dx * npc->dx + npc->dy * npc->dy);
}

void	update_npc(void *param)
{
	t_cub	*cub;
	t_npc	*npc;
	t_bfs	bfs;

	cub = (t_cub *)param;
	npc = cub->npc;
	if (!npc || !npc->active || cub->game_over || cub->you_win)
		return ;
	ft_memset(&bfs, 0, sizeof(t_bfs));
	bfs.now = get_time();
	get_length(cub, npc, &bfs, bfs.now);
	if (cub->npc->path_length < 2)
		return ;
	if (cub->npc->current_target >= cub->npc->path_length)
		return ;
	get_distance(cub, npc, &bfs);
	if (bfs.dist < 0.05)
	{
		cub->npc->current_target++;
		return ;
	}
	move_n_get_distance(cub, npc, &bfs);
	if (bfs.dist < NPC_CATCH_DIST)
		cub->game_over = true;
}

void	draw_npc(mlx_image_t *img, t_cub *cub)
{
	if (!cub->npc || !cub->npc->active)
	return ;
	cub->npc->offset_x = (int)((cub->npc->pos_x - cub->player->pos_x) * MINIMAP_TILE);
	cub->npc->offset_y = (int)((cub->npc->pos_y - cub->player->pos_y) * MINIMAP_TILE);
	if (cub->npc->offset_x < -MINIMAP_RADIUS * MINIMAP_TILE
		|| cub->npc->offset_x > MINIMAP_RADIUS * MINIMAP_TILE
		|| cub->npc->offset_y < -MINIMAP_RADIUS * MINIMAP_TILE
		|| cub->npc->offset_y > MINIMAP_RADIUS * MINIMAP_TILE)
		return ;
	cub->npc->view = (2 * MINIMAP_RADIUS + 1) * MINIMAP_TILE;
	cub->npc->minimap_x = WIDTH - MINIMAP_PADDING - cub->npc->view;
	cub->npc->minimap_y = MINIMAP_PADDING;
	cub->npc->screen_x = cub->npc->minimap_x + MINIMAP_RADIUS * MINIMAP_TILE + MINIMAP_TILE / 2 + cub->npc->offset_x;
	cub->npc->screen_y = cub->npc->minimap_y + MINIMAP_RADIUS * MINIMAP_TILE + MINIMAP_TILE / 2 + cub->npc->offset_y;
	cub->npc->ps = MINIMAP_TILE / 3;
	if (cub->npc->ps < 3)
		cub->npc->ps = 3;
	draw_tile(img, cub->npc->screen_x - cub->npc->ps / 2, cub->npc->screen_y - cub->npc->ps / 2, cub->npc->ps, BLUE);
}

void	draw_sprite(t_cub *cub, double *raycaster_buffer)
{
	t_dpoint	pos;

	if (!cub->npc || !cub->npc->active)
		return ;
	pos.x = cub->npc->pos_x;
	pos.y = cub->npc->pos_y;
	draw_billboard_sprite(cub, pos, cub->textures->police_tex,
		raycaster_buffer);
}
