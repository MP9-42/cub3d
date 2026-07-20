/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 01:05:12 by alegeber          #+#    #+#             */
/*   Updated: 2026/07/20 22:48:16 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_items(void *param)
{
	t_cub	*cub;
	int		px;
	int		py;
	char	tile;

	cub = (t_cub *)param;
	if (cub->game_over || cub->you_win)
		return ;
	px = (int)cub->player->pos_x;
	py = (int)cub->player->pos_y;
	if (py < 0 || py >= cub->map->size
		|| px < 0 || px >= cub->map->max_width)
		return ;
	tile = cub->map->rmap[py][px];
	if (tile == '7')
	{
		cub->map->rmap[py][px] = '0';
		cub->can_count++;
	}
	else if ((tile == '9' || tile == '8') && cub->can_count > 0)
		cub->you_win = true;
}

int	count_total_cans(t_map *map)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < map->size)
	{
		x = 0;
		while (x < map->max_width)
		{
			if (map->rmap[y][x] == '7')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	draw_cans(t_cub *cub, double *raycaster_buffer)
{
	int			y;
	int			x;
	t_dpoint	pos;

	y = 0;
	while (y < cub->map->size)
	{
		x = 0;
		while (x < cub->map->max_width)
		{
			if (cub->map->rmap[y][x] == '7')
			{
				pos.x = x + 0.5;
				pos.y = y + 0.5;
				draw_billboard_sprite(cub, pos,
					cub->textures->can_tex, raycaster_buffer);
			}
			x++;
		}
		y++;
	}
}

static void	draw_can_icon(mlx_image_t *img, mlx_texture_t *tex, int x0, int y0)
{
	int			x;
	int			y;
	int			tex_x;
	int			tex_y;
	uint8_t		*pixel;
	uint32_t	color;

	if (!tex)
		return ;
	y = 0;
	while (y < HUD_ICON_SIZE)
	{
		x = 0;
		while (x < HUD_ICON_SIZE)
		{
			tex_x = x * (int)tex->width / HUD_ICON_SIZE;
			tex_y = y * (int)tex->height / HUD_ICON_SIZE;
			pixel = &tex->pixels[(tex_y * tex->width + tex_x) * 4];
			if (pixel[3] != 0 && x0 + x < WIDTH && y0 + y < HEIGHT)
			{
				color = ((uint32_t)pixel[0] << 24)
					| ((uint32_t)pixel[1] << 16)
					| ((uint32_t)pixel[2] << 8) | pixel[3];
				mlx_put_pixel(img, x0 + x, y0 + y, color);
			}
			x++;
		}
		y++;
	}
}

static void	draw_can_dot(mlx_image_t *img, int x0, int y0)
{
	int	x;
	int	y;
	int	r;
	int	cx;
	int	cy;

	r = HUD_ICON_SIZE / 2 - 4;
	cx = x0 + HUD_ICON_SIZE / 2;
	cy = y0 + HUD_ICON_SIZE / 2;
	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			if (x * x + y * y <= r * r
				&& cx + x < WIDTH && cy + y < HEIGHT)
				mlx_put_pixel(img, cx + x, cy + y, HUD_DOT_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_can_hud(t_cub *cub)
{
	int	i;
	int	x0;

	i = 0;
	while (i < cub->total_cans)
	{
		x0 = HUD_MARGIN + i * (HUD_ICON_SIZE + HUD_ICON_GAP);
		if (i < cub->can_count)
			draw_can_icon(cub->game->img, cub->textures->can_tex,
				x0, HUD_MARGIN);
		else
			draw_can_dot(cub->game->img, x0, HUD_MARGIN);
		i++;
	}
}
