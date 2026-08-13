/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 16:50:12 by alegeber          #+#    #+#             */
/*   Updated: 2026/08/13 13:19:36 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// draws our player as a red point with a green line
// indicating the direction the player is facing
void	draw_player(mlx_image_t *img, t_cub *cub,
		int origin_x, int origin_y)
{
	int		cx;
	int		cy;
	int		ps;
	int		i;
	t_point	pt;

	cx = origin_x + MINIMAP_RADIUS * MINIMAP_TILE + MINIMAP_TILE / 2
		+ (int)((cub->player->pos_x - (int)cub->player->pos_x - 0.5)
			* MINIMAP_TILE);
	cy = origin_y + MINIMAP_RADIUS * MINIMAP_TILE + MINIMAP_TILE / 2
		+ (int)((cub->player->pos_y - (int)cub->player->pos_y - 0.5)
			* MINIMAP_TILE);
	ps = MINIMAP_TILE / 3;
	if (ps < 3)
		ps = 3;
	draw_tile(img, (t_point){cx - ps / 2, cy - ps / 2}, ps, RED);
	i = 0;
	while (i <= MINIMAP_TILE * 2)
	{
		pt.x = cx + (int)(cub->player->dir_x * i) - 1;
		pt.y = cy + (int)(cub->player->dir_y * i) - 1;
		draw_tile(img, pt, 2, GREEN);
		i++;
	}
}

static void	clamp_tile(t_point *start, t_point *end, mlx_image_t *img)
{
	if (start->x < 0)
		start->x = 0;
	if (start->y < 0)
		start->y = 0;
	if (end->x > (int)img->width)
		end->x = img->width;
	if (end->y > (int)img->height)
		end->y = img->height;
}

// draws our minimap tile by tile, clamping the start and
// end points to the image boundaries
void	draw_tile(mlx_image_t *img, t_point start, int size, uint32_t color)
{
	t_point	end;
	int		x;
	int		y;

	end.x = start.x + size;
	end.y = start.y + size;
	clamp_tile(&start, &end, img);
	y = start.y;
	while (y < end.y)
	{
		x = start.x;
		while (x < end.x)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
