/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 01:05:12 by alegeber          #+#    #+#             */
/*   Updated: 2026/07/21 16:42:37 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
