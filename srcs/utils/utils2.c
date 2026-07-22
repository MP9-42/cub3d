/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 14:14:07 by MP9               #+#    #+#             */
/*   Updated: 2026/07/22 14:15:27 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**deep_copy_map(t_map *map)
{
	char	**copy;
	int		bi;

	bi = 0;
	copy = ft_calloc(sizeof(char *), map->size);
	while (map->rmap[bi])
	{
		copy[bi] = ft_strdup(map->rmap[bi]);
		bi++;
	}
	return (copy);
}

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
