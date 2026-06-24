/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 15:37:17 by MP9               #+#    #+#             */
/*   Updated: 2026/06/24 14:49:44 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#define MINIMAP_PADDING 24
#define MINIMAP_BG 0x202020FF
#define MINIMAP_WALL 0xE0E0E0FF
#define MINIMAP_FLOOR 0x101010FF
#define MINIMAP_VOID 0x050505FF

static void	clear_image(mlx_image_t *img, uint32_t color)
{
	uint32_t	*pixels;
	uint32_t	total;
	uint32_t	i;

	pixels = (uint32_t *)img->pixels;
	total = img->width * img->height;
	i = 0;
	while (i < total)
	{
		pixels[i] = color;
		i++;
	}
}

static int	get_tile_size(t_game *game, t_map *map)
{
	int	available_w;
	int	available_h;
	int	tile_w;
	int	tile_h;

	available_w = game->width - (MINIMAP_PADDING * 2);
	available_h = game->height - (MINIMAP_PADDING * 2);
	if (available_w < map->max_width)
		available_w = map->max_width;
	if (available_h < map->size)
		available_h = map->size;
	tile_w = available_w / map->max_width;
	tile_h = available_h / map->size;
	if (tile_w < tile_h)
		tile_h = tile_w;
	if (tile_h < 1)
		tile_h = 1;
	return (tile_h);
}

static void	draw_player(mlx_image_t *img, t_cub *cub,
					int origin_x, int origin_y, int tile)
{
	int	player_px;
	int	player_py;
	int	player_size;
	int	line_len;
	int	i;

	player_px = origin_x + (int)(cub->player->pos_x * tile);
	player_py = origin_y + (int)(cub->player->pos_y * tile);
	player_size = tile / 3;
	if (player_size < 3)
		player_size = 3;
	draw_tile(img, player_px - (player_size / 2),
		player_py - (player_size / 2), player_size, RED);
	line_len = tile * 2;
	if (line_len < 12)
		line_len = 12;
	i = 0;
	while (i <= line_len)
	{
		draw_tile(img, player_px + (int)(cub->player->dir_x * i) - 1,
			player_py + (int)(cub->player->dir_y * i) - 1, 3, GREEN);
		i++;
	}
}

mlx_t	*init_window(t_cub *cub)
{
	mlx_t		*mlx;
	int32_t		monitor_w;
	int32_t		monitor_h;

	cub->game->width = WIDTH;
	cub->game->height = HEIGHT;
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!mlx)
		return (NULL);
	monitor_w = 0;
	monitor_h = 0;
	mlx_get_monitor_size(0, &monitor_w, &monitor_h);
	if (monitor_w > 0 && monitor_h > 0)
	{
		cub->game->width = monitor_w;
		cub->game->height = monitor_h;
		mlx_set_window_size(mlx, monitor_w, monitor_h);
	}
	else
	{
		cub->game->width = mlx->width;
		cub->game->height = mlx->height;
	}
	cub->game->mlx = mlx;
	cub->game->player = cub->player;
	cub->game->cub = cub;
	get_image(cub->game, cub);
	mlx_loop(mlx);
	return (mlx);
}

void	get_image(t_game *game, t_cub *cub)
{
	game->img = mlx_new_image(game->mlx, game->width, game->height);
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
	redraw(game);
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

void	render_map(mlx_image_t *img, t_cub *cub)
{
	t_map	*map;
	int		tile;
	int		x;
	int		y;
	int		origin_x;
	int		origin_y;

	map = cub->map;
	clear_image(img, MINIMAP_BG);
	tile = get_tile_size(cub->game, map);
	origin_x = (cub->game->width - (map->max_width * tile)) / 2;
	origin_y = (cub->game->height - (map->size * tile)) / 2;
	y = 0;
	while (y < map->size)
	{
		x = 0;
		while (x < map->max_width)
		{
			if (map->rmap[y][x] == '1')
				draw_tile(img, origin_x + (x * tile), origin_y + (y * tile),
					tile, MINIMAP_WALL);
			else if (map->rmap[y][x] == ' ')
				draw_tile(img, origin_x + (x * tile), origin_y + (y * tile),
					tile, MINIMAP_VOID);
			else
				draw_tile(img, origin_x + (x * tile), origin_y + (y * tile),
					tile, MINIMAP_FLOOR);
			x++;
		}
		y++;
	}
	draw_player(img, cub, origin_x, origin_y, tile);
}
