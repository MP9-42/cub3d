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

static uint32_t	wall_color(t_ray *ray)
{
	if (ray->side == 0 && ray->step_x > 0)
		return (0xD9534FFF);
	if (ray->side == 0)
		return (0xE8A33DFF);
	if (ray->step_y > 0)
		return (0x5CB85CFF);
	return (0x428BCAFF);
}

static void	draw_column(t_game *game, t_colors *colors, t_ray *ray, int x)
{
	int			y;
	int			h;
	uint32_t	color;

	h = HEIGHT;
	if (ray->perp_wall_dist < 0.01)
		ray->perp_wall_dist = 0.01;
	ray->line_height = (int)(h / ray->perp_wall_dist);
	ray->draw_start = h / 2 - ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = h / 2 + ray->line_height / 2;
	if (ray->draw_end >= h)
		ray->draw_end = h - 1;
	color = wall_color(ray);
	y = 0;
	while (y < ray->draw_start)
		mlx_put_pixel(game->img, x, y++, colors->ceiling);
	while (y <= ray->draw_end)
		mlx_put_pixel(game->img, x, y++, color);
	while (y < h)
		mlx_put_pixel(game->img, x, y++, colors->floor);
}

void	render_frame(void *param)
{
	t_cub	*cub;
	t_ray	ray;
	double	camera_x;
	int		x;
	int		w;

	cub = (t_cub *)param;
	w = WIDTH;
	x = 0;
	while (x < w)
	{
		camera_x = 2.0 * x / w - 1.0;
		cast_ray(cub->player, cub->map, &ray, camera_x);
		draw_column(cub->game, cub->colors, &ray, x);
		x++;
	}
	render_map(cub->game->img, cub);
}
