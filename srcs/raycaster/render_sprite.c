/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:39:51 by alegeber          #+#    #+#             */
/*   Updated: 2026/07/15 17:51:51 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Reads texel (tex_x, tex_y) from an MLX42 texture and packs its four
// RGBA bytes into the 0xRRGGBBAA format mlx_put_pixel expects.
uint32_t	tex_pixel_color(mlx_texture_t *tex, int tex_x, int tex_y)
{
	uint8_t	*pixel;

	pixel = &tex->pixels[(tex_y * tex->width + tex_x) * 4];
	return (((uint32_t)pixel[0] << 24) | ((uint32_t)pixel[1] << 16)
		| ((uint32_t)pixel[2] << 8) | pixel[3]);
}

// Transforms the sprite's world position into camera space via the
// inverse camera matrix; transform_y is its depth. Returns false when
// there is no texture or the sprite sits behind the player.
static bool	init_sprite(t_cub *cub, t_sprite *sp, t_dpoint pos,
				mlx_texture_t *tex)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	if (!tex)
		return (false);
	sp->tex = tex;
	sprite_x = pos.x - cub->player->pos_x;
	sprite_y = pos.y - cub->player->pos_y;
	inv_det = 1.0 / (cub->player->plane_x * cub->player->dir_y
			- cub->player->dir_x * cub->player->plane_y);
	sp->transform_x = inv_det * (cub->player->dir_y * sprite_x
			- cub->player->dir_x * sprite_y);
	sp->transform_y = inv_det * (-cub->player->plane_y * sprite_x
			+ cub->player->plane_x * sprite_y);
	return (sp->transform_y > 0);
}

// Derives the sprite's on-screen center, size (inversely proportional
// to depth) and its x/y draw range, clamped to the frame edges.
static void	set_sprite_bounds(t_sprite *sp)
{
	sp->screen_x = (int)((WIDTH / 2)
			* (1 + sp->transform_x / sp->transform_y));
	sp->height = (int)fabs(HEIGHT / sp->transform_y);
	sp->start_y = -sp->height / 2 + HEIGHT / 2;
	if (sp->start_y < 0)
		sp->start_y = 0;
	sp->end_y = sp->height / 2 + HEIGHT / 2;
	if (sp->end_y >= HEIGHT)
		sp->end_y = HEIGHT - 1;
	sp->width = (int)fabs(HEIGHT / sp->transform_y);
	sp->start_x = -sp->width / 2 + sp->screen_x;
	if (sp->start_x < 0)
		sp->start_x = 0;
	sp->end_x = sp->width / 2 + sp->screen_x;
	if (sp->end_x >= WIDTH)
		sp->end_x = WIDTH - 1;
}

// Draws one vertical stripe of the sprite, mapping each screen row to
// a texture row in 8.8 fixed-point (the *256 factors). Fully
// transparent texels (alpha 0) are skipped so the background shows.
static void	blit_sprite_column(t_cub *cub, t_sprite *sp, int stripe, int tex_x)
{
	int			y;
	int			tex_y;
	int			d;
	uint32_t	color;

	y = sp->start_y;
	while (y < sp->end_y)
	{
		d = y * 256 - HEIGHT * 128 + sp->height * 128;
		tex_y = ((d * (int)sp->tex->height) / sp->height) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)sp->tex->height)
			tex_y = sp->tex->height - 1;
		color = tex_pixel_color(sp->tex, tex_x, tex_y);
		if ((color & 0xFF) != 0)
			mlx_put_pixel(cub->game->img, stripe, y, color);
		y++;
	}
}

// Renders a camera-facing sprite at world position pos, stripe by
// stripe. Each stripe is depth-tested against raycaster_buffer (the
// wall distances) so walls correctly occlude the sprite.
void	draw_billboard_sprite(t_cub *cub, t_dpoint pos,
			mlx_texture_t *tex, double *raycaster_buffer)
{
	t_sprite	sp;
	int			stripe;
	int			tex_x;

	if (!init_sprite(cub, &sp, pos, tex))
		return ;
	set_sprite_bounds(&sp);
	stripe = sp.start_x;
	while (stripe < sp.end_x)
	{
		tex_x = (int)(256 * (stripe - (-sp.width / 2 + sp.screen_x))
				* tex->width / sp.width) / 256;
		if (stripe > 0 && stripe < WIDTH
			&& sp.transform_y < raycaster_buffer[stripe])
			blit_sprite_column(cub, &sp, stripe, tex_x);
		stripe++;
	}
}
