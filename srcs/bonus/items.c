/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 01:05:12 by alegeber          #+#    #+#             */
/*   Updated: 2026/08/12 19:14:22 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Per-frame hook: if the player is standing on a can tile ('7'), clears
// the tile and banks the can, then re-checks the finish since that may
// have been the last one. Frozen once the game is won or lost.
void	update_items(void *param)
{
	t_cub	*cub;
	int		px;
	int		py;
	char	tile;

	cub = (t_cub *)param;
	if (cub->game_over || cub->you_win)
		return ;
	px = (int)cub->player->pos_x;
	py = (int)cub->player->pos_y;
	if (py < 0 || py >= cub->map->size
		|| px < 0 || px >= cub->map->max_width)
		return ;
	tile = cub->map->rmap[py][px];
	if (tile == '7')
	{
		cub->map->rmap[py][px] = '0';
		cub->can_count++;
	}
	check_finish(cub);
}

// Counts the '7' tiles once at startup: the HUD draws one slot per can
// and the finish stays locked until can_count reaches this total.
int	count_total_cans(t_map *map)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < map->size)
	{
		x = 0;
		while (x < map->max_width)
		{
			if (map->rmap[y][x] == '7')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

// Draws every can still on the map as a billboard sprite centred on its
// tile. The raycaster buffer carries the per-column wall distances, so
// cans standing behind a wall stay hidden.
void	draw_cans(t_cub *cub, double *raycaster_buffer)
{
	int			y;
	int			x;
	t_dpoint	pos;

	y = 0;
	while (y < cub->map->size)
	{
		x = 0;
		while (x < cub->map->max_width)
		{
			if (cub->map->rmap[y][x] == '7')
			{
				pos.x = x + 0.5;
				pos.y = y + 0.5;
				draw_billboard_sprite(cub, pos,
					cub->textures->can_tex, raycaster_buffer);
			}
			x++;
		}
		y++;
	}
}
