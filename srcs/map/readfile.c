/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 13:21:07 by MP9               #+#    #+#             */
/*   Updated: 2026/08/13 13:22:58 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	readfile(t_parsing *parsing)
{
	int		capacity;
	int		i;

	capacity = 16;
	i = 0;
	parsing->file = malloc(sizeof(char *) * (capacity + 1));
	if (!parsing->file)
		return ;
	while (1)
	{
		rf_helper(parsing, &capacity, i);
		if (i >= capacity)
		{
			parsing->file[i] = NULL;
			return ;
		}
		parsing->file[i] = get_next_line(parsing->fd);
		if (!parsing->file[i])
			break ;
		i++;
	}
	parsing->file[i] = NULL;
}

int	map_maker(t_map *map, t_parsing *parsing, int start)
{
	int	i;
	int	mi;

	mi = 0;
	i = start;
	while (mi < map->size)
	{
		map->rmap[mi] = ft_linedup(parsing->file[i]);
		if (!map->rmap[mi])
			return (error_exit(2), 0);
		kill_n(map->rmap[mi]);
		mi++;
		i++;
	}
	map->rmap[map->size] = NULL;
	return (1);
}
