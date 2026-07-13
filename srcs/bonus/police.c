/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   police.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 18:59:12 by MP9               #+#    #+#             */
/*   Updated: 2026/07/02 19:06:34 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <sys/time.h>

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
				npc->pos_x = x + 0.5;
				npc->pos_y = y + 0.5;
				npc->speed = NPC_SPEED;
				npc->active = true;
				npc->path_length = 0;
				npc->current_target = 0;
				npc->last_path_time = 0;
				map->rmap[y][x] = '0';
				return (npc);
			}
			x++;
		}
		y++;
	}
	return (NULL);
}

static double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec * 0.000001);
}

static int	bfs(t_map *map, int sx, int sy, int ex, int ey,
		int *path_x, int *path_y)
{
	int		*visited;
	int		*par_x;
	int		*par_y;
	int		*qx;
	int		*qy;
	int		front;
	int		rear;
	int		dx[4];
	int		dy[4];
	int		i;
	int		nx;
	int		ny;
	int		cx;
	int		cy;
	int		len;
	int		idx;
	int		w;
	int		total;

	w = map->max_width;
	total = map->size * w;
	visited = ft_calloc(total, sizeof(int));
	par_x = ft_calloc(total, sizeof(int));
	par_y = ft_calloc(total, sizeof(int));
	qx = ft_calloc(total, sizeof(int));
	qy = ft_calloc(total, sizeof(int));
	if (!visited || !par_x || !par_y || !qx || !qy)
		return (free(visited), free(par_x), free(par_y),
			free(qx), free(qy), 0);
	front = 0;
	rear = 0;
	qx[rear] = sx;
	qy[rear] = sy;
	rear++;
	visited[sy * w + sx] = 1;
	dx[0] = 1;
	dy[0] = 0;
	dx[1] = -1;
	dy[1] = 0;
	dx[2] = 0;
	dy[2] = 1;
	dx[3] = 0;
	dy[3] = -1;
	while (front < rear)
	{
		cx = qx[front];
		cy = qy[front];
		front++;
		if (cx == ex && cy == ey)
			break ;
		i = 0;
		while (i < 4)
		{
			nx = cx + dx[i];
			ny = cy + dy[i];
			if (ny >= 0 && ny < map->size && nx >= 0 && nx < w
				&& map->rmap[ny][nx] != '1'
				&& !visited[ny * w + nx])
			{
				visited[ny * w + nx] = 1;
				par_x[ny * w + nx] = cx;
				par_y[ny * w + nx] = cy;
				qx[rear] = nx;
				qy[rear] = ny;
				rear++;
			}
			i++;
		}
	}
	if (!visited[ey * w + ex])
		return (free(visited), free(par_x), free(par_y),
			free(qx), free(qy), 0);
	len = 0;
	cx = ex;
	cy = ey;
	while (cx != sx || cy != sy)
	{
		if (len >= MAX_PATH - 1)
			break ;
		path_x[len] = cx;
		path_y[len] = cy;
		len++;
		idx = cy * w + cx;
		nx = par_x[idx];
		ny = par_y[idx];
		cx = nx;
		cy = ny;
	}
	path_x[len] = cx;
	path_y[len] = cy;
	len++;
	i = 0;
	while (i < len / 2)
	{
		nx = path_x[i];
		ny = path_y[i];
		path_x[i] = path_x[len - 1 - i];
		path_y[i] = path_y[len - 1 - i];
		path_x[len - 1 - i] = nx;
		path_y[len - 1 - i] = ny;
		i++;
	}
	free(visited);
	free(par_x);
	free(par_y);
	free(qx);
	free(qy);
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

void	update_npc(void *param)
{
	t_cub	*cub;
	double	now;
	double	target_x;
	double	target_y;
	double	dx;
	double	dy;
	double	dist;
	int		px;
	int		py;

	cub = (t_cub *)param;
	if (!cub->npc || !cub->npc->active || cub->game_over)
		return ;
	now = get_time();
	if (now - cub->npc->last_path_time > NPC_RECOMPUTE)
	{
		cub->npc->last_path_time = now;
		px = (int)cub->player->pos_x;
		py = (int)cub->player->pos_y;
		cub->npc->path_length = bfs(cub->map,
				(int)cub->npc->pos_x, (int)cub->npc->pos_y,
				px, py,
				cub->npc->path_x, cub->npc->path_y);
		cub->npc->current_target = 1;
	}
	if (cub->npc->path_length < 2)
		return ;
	if (cub->npc->current_target >= cub->npc->path_length)
		return ;
	target_x = cub->npc->path_x[cub->npc->current_target] + 0.5;
	target_y = cub->npc->path_y[cub->npc->current_target] + 0.5;
	dx = target_x - cub->npc->pos_x;
	dy = target_y - cub->npc->pos_y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist < 0.05)
	{
		cub->npc->current_target++;
		return ;
	}
	dx /= dist;
	dy /= dist;
	move_npc(cub, dx * cub->npc->speed, dy * cub->npc->speed);
	dx = cub->player->pos_x - cub->npc->pos_x;
	dy = cub->player->pos_y - cub->npc->pos_y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist < NPC_CATCH_DIST)
		cub->game_over = true;
}

void	draw_npc(mlx_image_t *img, t_cub *cub)
{
	int		view;
	int		ox;
	int		oy;
	int		cdx;
	int		cdy;
	int		cx;
	int		cy;
	int		ps;

	if (!cub->npc || !cub->npc->active)
		return ;
	cdx = (int)((cub->npc->pos_x - cub->player->pos_x) * MINIMAP_TILE);
	cdy = (int)((cub->npc->pos_y - cub->player->pos_y) * MINIMAP_TILE);
	if (cdx < -MINIMAP_RADIUS * MINIMAP_TILE
		|| cdx > MINIMAP_RADIUS * MINIMAP_TILE
		|| cdy < -MINIMAP_RADIUS * MINIMAP_TILE
		|| cdy > MINIMAP_RADIUS * MINIMAP_TILE)
		return ;
	view = (2 * MINIMAP_RADIUS + 1) * MINIMAP_TILE;
	ox = WIDTH - MINIMAP_PADDING - view;
	oy = MINIMAP_PADDING;
	cx = ox + MINIMAP_RADIUS * MINIMAP_TILE + MINIMAP_TILE / 2 + cdx;
	cy = oy + MINIMAP_RADIUS * MINIMAP_TILE + MINIMAP_TILE / 2 + cdy;
	ps = MINIMAP_TILE / 3;
	if (ps < 3)
		ps = 3;
	draw_tile(img, cx - ps / 2, cy - ps / 2, ps, BLUE);
}

void	draw_sprite(t_cub *cub, double *raycaster_buffer)
{
	t_npc			*npc;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				stripe;
	int				tex_x;
	int				tex_y;
	int				d;
	int				y;
	uint8_t			*pixel;
	uint32_t		color;
	mlx_texture_t	*tex;

	npc = cub->npc;
	if (!npc || !npc->active)
		return ;
	tex = cub->textures->police_tex;
	if (!tex)
		return ;
	sprite_x = npc->pos_x - cub->player->pos_x;
	sprite_y = npc->pos_y - cub->player->pos_y;
	inv_det = 1.0 / (cub->player->plane_x * cub->player->dir_y
			- cub->player->dir_x * cub->player->plane_y);
	transform_x = inv_det * (cub->player->dir_y * sprite_x
			- cub->player->dir_x * sprite_y);
	transform_y = inv_det * (-cub->player->plane_y * sprite_x
			+ cub->player->plane_x * sprite_y);
	if (transform_y <= 0)
		return ;
	sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
	sprite_height = abs((int)(HEIGHT / transform_y));
	draw_start_y = -sprite_height / 2 + HEIGHT / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = sprite_height / 2 + HEIGHT / 2;
	if (draw_end_y >= HEIGHT)
		draw_end_y = HEIGHT - 1;
	sprite_width = abs((int)(HEIGHT / transform_y));
	draw_start_x = -sprite_width / 2 + sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (draw_end_x >= WIDTH)
		draw_end_x = WIDTH - 1;
	stripe = draw_start_x;
	while (stripe < draw_end_x)
	{
		tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x))
				* tex->width / sprite_width) / 256;
		if (stripe > 0 && stripe < WIDTH
			&& transform_y < raycaster_buffer[stripe])
		{
			y = draw_start_y;
			while (y < draw_end_y)
			{
				d = y * 256 - HEIGHT * 128 + sprite_height * 128;
				tex_y = ((d * tex->height) / sprite_height) / 256;
				if (tex_y < 0)
					tex_y = 0;
				if (tex_y >= (int)tex->height)
					tex_y = tex->height - 1;
				pixel = &tex->pixels[(tex_y * tex->width + tex_x) * 4];
				if (pixel[3] != 0)
				{
					color = (pixel[0] << 24) | (pixel[1] << 16)
						| (pixel[2] << 8) | pixel[3];
					mlx_put_pixel(cub->game->img, stripe, y, color);
				}
				y++;
			}
		}
		stripe++;
	}
}
