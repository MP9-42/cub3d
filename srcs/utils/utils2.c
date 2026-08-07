/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 14:14:07 by MP9               #+#    #+#             */
/*   Updated: 2026/08/07 15:21:00 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


void	free_map(char **map, int size)
{
	int	i;

	if (!map)
		return ;
	i = size - 1;
	while (i >= 0)
	{
		free(map[i]);
		i--;
	}
	free(map);
}

void	tab_converter(const char *s1, char *s2, size_t *i, size_t *j)
{
	while (s1[(*i)])
	{
		if (s1[(*i)] == '\t')
		{
			s2[(*j)++] = ' ';
			s2[(*j)++] = ' ';
			s2[(*j)++] = ' ';
			s2[(*j)++] = ' ';
		}
		else
			s2[(*j)++] = s1[(*i)];
		(*i)++;
	}
}

void	line_cruncher(t_map *map, t_rowcols *rowcols)
{
	rowcols->value = (free_map(rowcols->padded, map->size),
			free_map(rowcols->copy, map->size), false);
}
