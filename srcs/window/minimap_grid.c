/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 16:45:19 by alegeber          #+#    #+#             */
/*   Updated: 2026/07/21 17:04:36 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static uint32_t	tile_color(t_cub *cub, int map_x, int map_y)
{
	char	tile;

	tile = map_tile(cub->map, map_x, map_y);
	if (tile == '\0' || tile == ' ')
		return (MINIMAP_VOID);
	if (tile == FINISH_TILE)
	{
		if (finish_unlocked(cub))
			return (MINIMAP_FINISH);
		return (MINIMAP_FINISH_LOCKED);
	}
	if (tile == '1')
		return (MINIMAP_WALL);
	return (MINIMAP_FLOOR);
}

static void	draw_minimap_tiles(mlx_image_t *img, t_cub *cub, t_point origin)
{
	int		dx;
	int		dy;
	t_point	pos;

	dy = -MINIMAP_RADIUS;
	while (dy <= MINIMAP_RADIUS)
	{
		dx = -MINIMAP_RADIUS;
		while (dx <= MINIMAP_RADIUS)
		{
			pos.x = origin.x + (dx + MINIMAP_RADIUS) * MINIMAP_TILE;
			pos.y = origin.y + (dy + MINIMAP_RADIUS) * MINIMAP_TILE;
			draw_tile(img, pos, MINIMAP_TILE,
				tile_color(cub, (int)cub->player->pos_x + dx,
					(int)cub->player->pos_y + dy));
			dx++;
		}
		dy++;
	}
}

void	render_map(mlx_image_t *img, t_cub *cub)
{
	t_point	origin;
	int		view;

	view = (2 * MINIMAP_RADIUS + 1) * MINIMAP_TILE;
	origin.x = WIDTH - MINIMAP_PADDING - view;
	origin.y = MINIMAP_PADDING;
	draw_minimap_tiles(img, cub, origin);
	draw_player(img, cub, origin.x, origin.y);
	draw_npc(img, cub);
}
