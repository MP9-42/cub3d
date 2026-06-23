/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 15:37:17 by MP9               #+#    #+#             */
/*   Updated: 2026/06/23 15:18:44 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


mlx_t	*init_window(t_cub *cub)
{
	mlx_t		*mlx;
	t_window	*window;

	window = ft_calloc(sizeof(t_window), 1);
	mlx_get_monitor_size(0, &window->width, &window->height);
	cub->game->window = window;
	mlx = mlx_init(window->width, window->height, "cub3d", true);
	if (!mlx)
		return (NULL);
	cub->game->mlx = mlx;
	get_image(cub->game, cub);
	mlx_loop(mlx);
	return (mlx);
}

void	get_image(t_game *game, t_cub *cub)
{
	t_window	*window;

	window = game->window;
	game->img = mlx_new_image(game->mlx, window->width, window->height);
	if (!game->img)
		return ;
	render_map(game->img, cub->map);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_resize_hook(game->mlx, resize_hook, game);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_game	*game;

	game = param;
	game->window->width = width;
	game->window->height = height;
	redraw(game);
}

void	redraw(t_game *game)
{
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, game->window->width,
			game->window->height);
	if (!game->img)
		return ;
	// render_scene(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void	draw_tile(mlx_image_t *img, int start_x, int start_y,
		int size, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_put_pixel(img, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	render_map(mlx_image_t *img, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->rmap[y])
	{
		x = 0;
		while (x < map->max_width)
		{
			if (map->rmap[y][x] == '1')
				draw_tile(img, x * TILE, y * TILE, TILE, WHITE);
			else
				draw_tile(img, x * TILE, y * TILE, TILE, BLACK);
			x++;
		}
		y++;
	}
}
