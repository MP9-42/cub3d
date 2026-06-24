/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 15:37:17 by MP9               #+#    #+#             */
/*   Updated: 2026/06/24 15:32:54 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define MINIMAP_PADDING 16
#define MINIMAP_TILE 8
#define MINIMAP_RADIUS 10
#define MINIMAP_WALL 0xE0E0E0CC
#define MINIMAP_FLOOR 0x202020CC
#define MINIMAP_VOID 0x111111CC

static void	draw_player(mlx_image_t *img, t_cub *cub, int origin_x, int origin_y)
{
	int		cx;
	int		cy;
	int		ps;
	int		i;

	cx = origin_x + MINIMAP_RADIUS * MINIMAP_TILE + MINIMAP_TILE / 2
		+ (int)((cub->player->pos_x - (int)cub->player->pos_x - 0.5)
		* MINIMAP_TILE);
	cy = origin_y + MINIMAP_RADIUS * MINIMAP_TILE + MINIMAP_TILE / 2
		+ (int)((cub->player->pos_y - (int)cub->player->pos_y - 0.5)
		* MINIMAP_TILE);
	ps = MINIMAP_TILE / 3;
	if (ps < 3)
		ps = 3;
	draw_tile(img, cx - ps / 2, cy - ps / 2, ps, RED);
	i = 0;
	while (i <= MINIMAP_TILE * 2)
	{
		draw_tile(img, cx + (int)(cub->player->dir_x * i) - 1,
			cy + (int)(cub->player->dir_y * i) - 1, 2, GREEN);
		i++;
	}
}

mlx_t	*init_window(t_cub *cub)
{
	mlx_t		*mlx;

	cub->game->width = WIDTH;
	cub->game->height = HEIGHT;
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!mlx)
		return (NULL);
	cub->game->mlx = mlx;
	cub->game->player = cub->player;
	cub->game->cub = cub;
	get_image(cub->game, cub);
	mlx_loop_hook(mlx, update_player, cub);
	mlx_loop_hook(mlx, render_frame, cub);
	mlx_loop(mlx);
	return (mlx);
}

void	get_image(t_game *game, t_cub *cub)
{
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return ;
	render_map(game->img, cub);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_resize_hook(game->mlx, resize_hook, game);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_game	*game;

	game = param;
	game->width = width;
	game->height = height;
}

void	redraw(t_game *game)
{
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, game->width, game->height);
	if (!game->img)
		return ;
	render_map(game->img, game->cub);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void	draw_tile(mlx_image_t *img, int start_x, int start_y,
		int size, uint32_t color)
{
	int	x;
	int	y;
	int	end_x;
	int	end_y;

	end_x = start_x + size;
	end_y = start_y + size;
	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;
	if (end_x > (int)img->width)
		end_x = img->width;
	if (end_y > (int)img->height)
		end_y = img->height;
	y = start_y;
	while (y < end_y)
	{
		x = start_x;
		while (x < end_x)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

static uint32_t	tile_color(t_map *map, int map_x, int map_y)
{
	if (map_y < 0 || map_y >= map->size
		|| map_x < 0 || map_x >= map->max_width)
		return (MINIMAP_VOID);
	if (map->rmap[map_y][map_x] == '1')
		return (MINIMAP_WALL);
	if (map->rmap[map_y][map_x] == ' ')
		return (MINIMAP_VOID);
	return (MINIMAP_FLOOR);
}

void	render_map(mlx_image_t *img, t_cub *cub)
{
	int		dx;
	int		dy;
	int		origin_x;
	int		origin_y;
	int		view;

	view = (2 * MINIMAP_RADIUS + 1) * MINIMAP_TILE;
	origin_x = WIDTH - MINIMAP_PADDING - view;
	origin_y = MINIMAP_PADDING;
	dy = -MINIMAP_RADIUS;
	while (dy <= MINIMAP_RADIUS)
	{
		dx = -MINIMAP_RADIUS;
		while (dx <= MINIMAP_RADIUS)
		{
			draw_tile(img,
				origin_x + (dx + MINIMAP_RADIUS) * MINIMAP_TILE,
				origin_y + (dy + MINIMAP_RADIUS) * MINIMAP_TILE,
				MINIMAP_TILE,
				tile_color(cub->map,
					(int)cub->player->pos_x + dx,
					(int)cub->player->pos_y + dy));
			dx++;
		}
		dy++;
	}
	draw_player(img, cub, origin_x, origin_y);
}
