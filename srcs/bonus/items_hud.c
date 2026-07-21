/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:12:53 by alegeber          #+#    #+#             */
/*   Updated: 2026/07/21 16:42:30 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	put_can_pixel(mlx_image_t *img, mlx_texture_t *tex,
		t_point px, t_point origin)
{
	int			tex_x;
	int			tex_y;
	uint8_t		*pixel;
	uint32_t	color;

	tex_x = px.x * (int)tex->width / HUD_ICON_SIZE;
	tex_y = px.y * (int)tex->height / HUD_ICON_SIZE;
	pixel = &tex->pixels[(tex_y * tex->width + tex_x) * 4];
	if (pixel[3] == 0
		|| origin.x + px.x >= WIDTH || origin.y + px.y >= HEIGHT)
		return ;
	color = ((uint32_t)pixel[0] << 24)
		| ((uint32_t)pixel[1] << 16)
		| ((uint32_t)pixel[2] << 8) | pixel[3];
	mlx_put_pixel(img, origin.x + px.x, origin.y + px.y, color);
}

static void	draw_can_icon(mlx_image_t *img, mlx_texture_t *tex, int x0, int y0)
{
	t_point	origin;
	t_point	px;

	if (!tex)
		return ;
	origin.x = x0;
	origin.y = y0;
	px.y = 0;
	while (px.y < HUD_ICON_SIZE)
	{
		px.x = 0;
		while (px.x < HUD_ICON_SIZE)
		{
			put_can_pixel(img, tex, px, origin);
			px.x++;
		}
		px.y++;
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
