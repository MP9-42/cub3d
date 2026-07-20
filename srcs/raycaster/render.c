/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:45:11 by alegeber          #+#    #+#             */
/*   Updated: 2026/07/15 14:00:00 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Floods the whole frame with one solid color; used for the
// win/lose end screens.
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

// Returns true once the game is over (caught or all cans collected),
// drawing the red/green overlay exactly once so later frames skip
// all rendering work.
static bool	check_game_end(t_cub *cub)
{
	if (!cub->game_over && !cub->you_win)
		return (false);
	if (!cub->overlay_drawn)
	{
		if (cub->game_over)
			draw_overlay(cub->game->img, 0xAA0000FF);
		else
			draw_overlay(cub->game->img, 0x00AA00FF);
		cub->overlay_drawn = true;
	}
	return (true);
}

// Per-frame MLX loop hook: casts one ray per screen column, draws the
// wall columns while filling the depth buffer, then layers the NPC
// sprite, cans, minimap and HUD on top.
void	render_frame(void *param)
{
	t_cub	*cub;
	t_ray	ray;
	double	raycaster_buffer[WIDTH];
	int		x;

	cub = (t_cub *)param;
	if (check_game_end(cub))
		return ;
	x = 0;
	while (x < WIDTH)
	{
		cast_ray(cub->player, cub->map, &ray, 2.0 * x / WIDTH - 1.0);
		draw_column(cub, &ray, x);
		raycaster_buffer[x] = ray.perp_wall_dist;
		x++;
	}
	draw_sprite(cub, raycaster_buffer);
	draw_cans(cub, raycaster_buffer);
	render_map(cub->game->img, cub);
	draw_can_hud(cub);
}
