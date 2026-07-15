/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:45:11 by alegeber          #+#    #+#             */
/*   Updated: 2026/07/15 12:55:18 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_column(t_game *game, t_textures *textures, t_player *player,
			t_colors *colors, t_ray *ray, int x)
{
	int				y;
	int				h;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	uint8_t			*pixel;
	uint32_t		color;
	mlx_texture_t	*tex;

	h = HEIGHT;
	if (ray->perp_wall_dist < 0.01)
		ray->perp_wall_dist = 0.01;
	ray->line_height = (int)(h / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + h / 2;
	if (ray->draw_end >= h)
		ray->draw_end = h - 1;
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			tex = textures->east_tex;
		else
			tex = textures->west_tex;
	}
	else
	{
		if (ray->step_y > 0)
			tex = textures->south_tex;
		else
			tex = textures->north_tex;
	}
	if (ray->side == 0)
		wall_x = player->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = player->pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (ray->side == 0 && ray->step_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->step_y < 0)
		tex_x = tex->width - tex_x - 1;
	y = 0;
	while (y < ray->draw_start)
		mlx_put_pixel(game->img, x, y++, colors->ceiling);
	step = (double)tex->height / ray->line_height;
	tex_pos = (ray->draw_start - h / 2 + ray->line_height / 2) * step;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= (int)tex->height)
			tex_y = tex->height - 1;
		tex_pos += step;
		pixel = &tex->pixels[(tex_y * tex->width + tex_x) * 4];
		color = ((uint32_t)pixel[0] << 24) | ((uint32_t)pixel[1] << 16)
			| ((uint32_t)pixel[2] << 8) | pixel[3];
		mlx_put_pixel(game->img, x, y++, color);
	}
	while (y < h)
		mlx_put_pixel(game->img, x, y++, colors->floor);
}

static void	draw_overlay(mlx_image_t *img, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			mlx_put_pixel(img, x++, y, color);
		y++;
	}
}

static void	blit_sprite_column(t_cub *cub, mlx_texture_t *tex, int stripe,
			int tex_x, int draw_start_y, int draw_end_y, int sprite_height)
{
	int			y;
	int			tex_y;
	int			d;
	uint8_t		*pixel;
	uint32_t	color;

	y = draw_start_y;
	while (y < draw_end_y)
	{
		d = y * 256 - HEIGHT * 128 + sprite_height * 128;
		tex_y = ((d * (int)tex->height) / sprite_height) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)tex->height)
			tex_y = tex->height - 1;
		pixel = &tex->pixels[(tex_y * tex->width + tex_x) * 4];
		if (pixel[3] != 0)
		{
			color = ((uint32_t)pixel[0] << 24)
				| ((uint32_t)pixel[1] << 16)
				| ((uint32_t)pixel[2] << 8) | pixel[3];
			mlx_put_pixel(cub->game->img, stripe, y, color);
		}
		y++;
	}
}

void	draw_billboard_sprite(t_cub *cub, double wx, double wy,
		mlx_texture_t *tex, double *raycaster_buffer)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		stripe;
	int		tex_x;

	if (!tex)
		return ;
	sprite_x = wx - cub->player->pos_x;
	sprite_y = wy - cub->player->pos_y;
	inv_det = 1.0 / (cub->player->plane_x * cub->player->dir_y
			- cub->player->dir_x * cub->player->plane_y);
	transform_x = inv_det * (cub->player->dir_y * sprite_x
			- cub->player->dir_x * sprite_y);
	transform_y = inv_det * (-cub->player->plane_y * sprite_x
			+ cub->player->plane_x * sprite_y);
	if (transform_y <= 0)
		return ;
	sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
	sprite_height = abs((int)(HEIGHT / transform_y));
	draw_start_y = -sprite_height / 2 + HEIGHT / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = sprite_height / 2 + HEIGHT / 2;
	if (draw_end_y >= HEIGHT)
		draw_end_y = HEIGHT - 1;
	sprite_width = abs((int)(HEIGHT / transform_y));
	draw_start_x = -sprite_width / 2 + sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (draw_end_x >= WIDTH)
		draw_end_x = WIDTH - 1;
	stripe = draw_start_x;
	while (stripe < draw_end_x)
	{
		tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x))
				* tex->width / sprite_width) / 256;
		if (stripe > 0 && stripe < WIDTH
			&& transform_y < raycaster_buffer[stripe])
			blit_sprite_column(cub, tex, stripe, tex_x,
				draw_start_y, draw_end_y, sprite_height);
		stripe++;
	}
}

void	render_frame(void *param)
{
	t_cub	*cub;
	t_ray	ray;
	double	camera_x;
	double	raycaster_buffer[WIDTH];
	int		x;
	int		w;

	cub = (t_cub *)param;
	if (cub->game_over || cub->you_win)
	{
		if (!cub->overlay_drawn)
		{
			if (cub->game_over)
				draw_overlay(cub->game->img, 0xAA0000FF);
			else
				draw_overlay(cub->game->img, 0x00AA00FF);
			cub->overlay_drawn = true;
		}
		return ;
	}
	w = WIDTH;
	x = 0;
	while (x < w)
	{
		camera_x = 2.0 * x / w - 1.0;
		cast_ray(cub->player, cub->map, &ray, camera_x);
		draw_column(cub->game, cub->textures, cub->player, cub->colors, &ray, x);
		raycaster_buffer[x] = ray.perp_wall_dist;
		x++;
	}
	draw_sprite(cub, raycaster_buffer);
	draw_cans(cub, raycaster_buffer);
	render_map(cub->game->img, cub);
	draw_can_hud(cub);
}
