/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 14:32:06 by alegeber          #+#    #+#             */
/*   Updated: 2026/07/15 17:51:33 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Projects the wall distance into a slice height on screen and clamps
// the slice's start/end rows to the visible frame.
static void	set_line_bounds(t_ray *ray)
{
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

// Picks the wall texture: the finish tile has its own texture on every
// face, otherwise N/S/E/W from which gridline side the ray hit (x-side
// or y-side) and the direction it was travelling.
static mlx_texture_t	*select_texture(t_cub *cub, t_ray *ray)
{
	if (is_finish_hit(cub, ray))
		return (cub->textures->finish_tex);
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (cub->textures->east_tex);
		return (cub->textures->west_tex);
	}
	if (ray->step_y > 0)
		return (cub->textures->south_tex);
	return (cub->textures->north_tex);
}

// Finds where along the wall tile the ray hit (fractional part) and
// scales it to a texture column, mirroring for the two wall
// orientations that would otherwise render flipped.
static int	get_tex_x(t_player *player, t_ray *ray, mlx_texture_t *tex)
{
	double	wall_x;
	int		tex_x;

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
	return (tex_x);
}

// Draws the textured part of screen column x, stepping tex_pos down
// the texture at a rate that stretches/shrinks it to line_height
// (which may exceed the screen for very close walls).
static void	draw_wall_tex(t_cub *cub, t_ray *ray, mlx_texture_t *tex, int x)
{
	int		tex_x;
	int		tex_y;
	int		y;
	double	step;
	double	tex_pos;

	tex_x = get_tex_x(cub->player, ray, tex);
	step = (double)tex->height / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= (int)tex->height)
			tex_y = tex->height - 1;
		tex_pos += step;
		mlx_put_pixel(cub->game->img, x, y++,
			wall_pixel(cub, tex, tex_x, tex_y));
	}
}

// Renders one full screen column for a cast ray: ceiling color above
// the wall slice, the textured slice itself, floor color below.
// Clamps perp_wall_dist to avoid division blow-up at point-blank range.
void	draw_column(t_cub *cub, t_ray *ray, int x)
{
	mlx_texture_t	*tex;
	int				y;

	if (ray->perp_wall_dist < 0.01)
		ray->perp_wall_dist = 0.01;
	set_line_bounds(ray);
	tex = select_texture(cub, ray);
	y = 0;
	while (y < ray->draw_start)
		mlx_put_pixel(cub->game->img, x, y++, cub->colors->ceiling);
	draw_wall_tex(cub, ray, tex, x);
	y = ray->draw_end + 1;
	while (y < HEIGHT)
		mlx_put_pixel(cub->game->img, x, y++, cub->colors->floor);
}
