/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:27 by MP9               #+#    #+#             */
/*   Updated: 2026/07/22 14:11:57 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	help_for_help(t_map *map, t_rowcols rowcols)
{
	free_map(rowcols.copy, map->size);
	free_map(map->rmap, map->size);
	map->rmap = rowcols.padded;
}

bool	validate_helper(t_map *map, t_rowcols rowcols, bool *value)
{
	int	bi;
	int	si;

	bi = 0;
	while (rowcols.copy[bi])
	{
		si = 0;
		while (rowcols.copy[bi][si])
		{
			if (ft_strchr("NSEW", rowcols.copy[bi][si]))
			{
				if (!flood_fill(rowcols.copy, bi, si, rowcols))
				{
					*value = (free_map(rowcols.padded, map->size),
							free_map(rowcols.copy, map->size), false);
					return (true);
				}
				help_for_help(map, rowcols);
				return (true);
			}
			si++;
		}
		bi++;
	}
	return (false);
}

bool	validate_map(t_map *map)
{
	bool		value;
	t_rowcols	rowcols;

	if (!valid_chars(map->rmap))
		return (false);
	map->max_width = get_max_width(map->rmap);
	rowcols.padded = pad_map(map->rmap, map->size, map->max_width);
	rowcols.copy = pad_map(map->rmap, map->size, map->max_width);
	if (!rowcols.padded || !rowcols.copy)
		return (free_map(rowcols.padded, map->size),
			free_map(rowcols.copy, map->size), false);
	rowcols.cols = map->max_width;
	rowcols.rows = map->size;
	if (validate_helper(map, rowcols, &value))
		return (value);
	free_map(rowcols.padded, map->size);
	free_map(rowcols.copy, map->size);
	return (false);
}

int	get_max_width(char **map)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

char	**pad_map(char **map, int rows, int max_width)
{
	char	**padded;
	int		i;
	int		len;
	int		j;

	padded = malloc(sizeof(char *) * (rows + 1));
	if (!padded)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		padded[i] = malloc(max_width + 1);
		if (!padded[i])
			return (NULL);
		len = ft_strlen(map[i]);
		ft_memcpy(padded[i], map[i], len);
		j = len;
		while (j < max_width)
			padded[i][j++] = ' ';
		padded[i][max_width] = '\0';
		i++;
	}
	padded[rows] = NULL;
	return (padded);
}
