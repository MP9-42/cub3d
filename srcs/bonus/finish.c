/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 16:10:00 by alegeber          #+#    #+#             */
/*   Updated: 2026/08/07 16:10:00 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// The finish only opens once every can on the map has been picked up.
bool	finish_unlocked(t_cub *cub)
{
	return (cub->can_count >= cub->total_cans);
}

// True when the ray ended on a finish tile, so the caller textures the
// column with the finish texture instead of the N/S/E/W walls.
bool	is_finish_hit(t_cub *cub, t_ray *ray)
{
	return (map_tile(cub->map, ray->map_x, ray->map_y) == FINISH_TILE);
}

// Reads one texel for a wall column, dimming it while the finish is
// still locked so the exit visibly lights up on the last can.
uint32_t	wall_pixel(t_cub *cub, mlx_texture_t *tex, int tx, int ty)
{
	uint32_t	c;

	c = tex_pixel_color(tex, tx, ty);
	if (tex != cub->textures->finish_tex || finish_unlocked(cub))
		return (c);
	return (((((c >> 24) & 0xFF) / FINISH_LOCK_SHADE) << 24)
		| ((((c >> 16) & 0xFF) / FINISH_LOCK_SHADE) << 16)
		| ((((c >> 8) & 0xFF) / FINISH_LOCK_SHADE) << 8)
		| (c & 0xFF));
}

// True when the player is pressed up against a finish tile: any '9' in
// the 3x3 block around them whose box the player is within
// FINISH_TOUCH of, on both axes.
bool	touching_finish(t_cub *cub)
{
	int		x;
	int		y;
	double	dx;
	double	dy;

	y = (int)cub->player->pos_y - 1;
	while (y <= (int)cub->player->pos_y + 1)
	{
		x = (int)cub->player->pos_x - 1;
		while (x <= (int)cub->player->pos_x + 1)
		{
			dx = fabs(cub->player->pos_x - (x + 0.5));
			dy = fabs(cub->player->pos_y - (y + 0.5));
			if (map_tile(cub->map, x, y) == FINISH_TILE
				&& dx < 0.5 + FINISH_TOUCH && dy < 0.5 + FINISH_TOUCH)
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}

// Wins the game when the player touches an unlocked finish wall.
void	check_finish(t_cub *cub)
{
	if (finish_unlocked(cub) && touching_finish(cub))
		cub->you_win = true;
}
