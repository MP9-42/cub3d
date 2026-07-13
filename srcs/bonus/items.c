/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 01:05:12 by alegeber          #+#    #+#             */
/*   Updated: 2026/07/10 15:52:38 by alegeber         ###   ########.fr       */
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
	else if (tile == '9' || tile == '8')
		cub->you_win = true;
}
