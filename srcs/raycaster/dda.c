/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 18:11:15 by alegeber          #+#    #+#             */
/*   Updated: 2026/06/24 14:07:16 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Returns 1 if the map cell (x, y) is a wall. Coordinates outside the
// map (or past the end of a short row) are treated as solid walls so
// rays can never escape the grid. The finish tile is solid too: it is
// a wall the player has to walk up to, not a floor to step on.
int	is_wall(t_map *map, int x, int y)
{
	char	tile;

	tile = map_tile(map, x, y);
	if (tile == '\0')
		return (1);
	return (tile == '1' || tile == FINISH_TILE);
}

// Sets the ray's starting grid cell to the player's cell and computes
// delta_dist: the distance the ray travels between two gridlines on
// each axis (1e30 stands in for infinity on axis-parallel rays).
static void	init_dda(t_player *player, t_ray *ray)
{
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

// Picks the grid step direction (+1/-1) per axis from the ray's sign
// and computes side_dist: the distance from the player to the first
// x- and y-gridline crossing.
static void	init_step_side(t_player *player, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

// Runs the DDA loop: repeatedly jumps to the nearest gridline crossing
// (whichever side_dist is smaller) until a wall cell is hit, recording
// whether that wall was hit on an x-side (0) or y-side (1).
static void	perform_dda(t_map *map, t_ray *ray)
{
	while (!is_wall(map, ray->map_x, ray->map_y))
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
}

// Casts one ray for screen column camera_x (-1..1 across the camera
// plane) and fills the ray struct, ending with perp_wall_dist: the
// wall distance projected onto the view direction (no fisheye).
void	cast_ray(t_player *player, t_map *map, t_ray *ray, double camera_x)
{
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
	init_dda(player, ray);
	init_step_side(player, ray);
	perform_dda(map, ray);
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}
