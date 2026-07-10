/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:45:11 by alegeber          #+#    #+#             */
/*   Updated: 2026/06/24 14:02:58 by alegeber         ###   ########.fr       */
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
		color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
		mlx_put_pixel(game->img, x, y++, color);
	}
	while (y < h)
		mlx_put_pixel(game->img, x, y++, colors->floor);
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
	render_map(cub->game->img, cub);
}
