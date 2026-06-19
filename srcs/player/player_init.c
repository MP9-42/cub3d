/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 12:00:00 by alegeber          #+#    #+#             */
/*   Updated: 2026/06/19 12:57:09 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_dir_plane_ns(t_player *p, char facing)
{
	if (facing == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
}

static void	set_dir_plane(t_player *p, char facing)
{
	if (facing == 'N' || facing == 'S')
		set_dir_plane_ns(p, facing);
	else if (facing == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

static int	find_spawn(t_player *player, char **rmap)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (rmap[y])
	{
		x = 0;
		while (rmap[y][x] && rmap[y][x] != '\n')
		{
			c = rmap[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				player->pos_x = x + 0.5;
				player->pos_y = y + 0.5;
				set_dir_plane(player, c);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

t_player	*init_player(t_map *map)
{
	t_player	*player;

	player = ft_calloc(sizeof(t_player), 1);
	if (!player)
		return (NULL);
	if (!find_spawn(player, map->rmap))
		return (free(player), NULL);
	return (player);
}
