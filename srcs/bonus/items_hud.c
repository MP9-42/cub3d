/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:12:53 by alegeber          #+#    #+#             */
/*   Updated: 2026/08/12 19:14:08 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Copies one pixel of the can icon into the frame: maps the HUD pixel
// back to a texel (nearest neighbour, since the icon is scaled down to
// HUD_ICON_SIZE), drops fully transparent texels and anything that would
// land outside the window, then packs the RGBA bytes the way MLX42
// expects them.
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

// Blits the can texture as one HUD_ICON_SIZE square with its top-left
// corner at x0/y0.
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

// Draws the placeholder for a can not collected yet: a filled circle
// inscribed in the same square an icon would occupy.
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

// Draws the top-left counter, one slot per can on the map laid out left
// to right: an icon for each can already collected, a dot for each one
// still out there.
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
