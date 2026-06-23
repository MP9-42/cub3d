/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:29:14 by alegeber          #+#    #+#             */
/*   Updated: 2026/06/23 14:42:31 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Returns 1 if the grid cell (x, y) is out of bounds or a wall tile ('1').
// Used by perform_dda to know when the ray has hit something.
static int is_wall(t_map *map, int x, int y)
{
	int	len;

	if (y < 0 || y >= map->size || x < 0)
		return 1;
	len = ft_strlen(map->rmap[y]);
	if (x >= len)
		return 1;
	return (map->rmap[y][x] == '1');
}

// Sets the starting grid cell and computes delta_dist: how far the ray travels
// to cross one full grid unit in X and Y. Zero direction gets near-infinity.
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

// Determines the step direction (-1 or +1) for each axis and computes side_dist:
// the distance from the player to the very first grid line crossing in X and Y.
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
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x);
		ray->side_dist_x *= ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y);
		ray->side_dist_y *= ray->delta_dist_y;
	}
}

// Marches the ray through the grid one tile at a time, always stepping the axis
// whose next crossing is closer, until a wall tile is hit. Sets ray->side (0=vertical, 1=horizontal).
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

// Entry point for raycasting: computes the ray direction from camera_x (-1 to +1),
// runs the full DDA, then stores perp_wall_dist (used to calculate wall stripe height).
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
