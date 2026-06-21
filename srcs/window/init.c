/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 15:37:17 by MP9               #+#    #+#             */
/*   Updated: 2026/06/21 17:10:34 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

mlx_t *init_window(t_cub *cub)
{
	mlx_t *mlx = ft_calloc(sizeof(mlx_t), 1);
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	get_image(cub->game, cub);
	mlx_loop(mlx);
	return(mlx);
}

void	get_image(t_game *game, t_cub *cub)
{
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	render_map(game->img, cub->map);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void draw_tile(mlx_image_t *img, int start_x, int start_y, int size, uint32_t color)
{
	int x;
	int y;

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

void render_map(mlx_image_t *img, t_map *map)
{
	int x;
	int y;

	y = 0;
	while(map->rmap[y])
	{
		x = 0;
		while (map->rmap[y][x])
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
