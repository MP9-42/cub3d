/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:27 by MP9               #+#    #+#             */
/*   Updated: 2026/06/19 15:47:53 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool flood_fill(char **map, int row, int col, t_rowcols rowcols)
{
	if (row < 0 || col < 0 || row >= rowcols.rows || col >= rowcols.cols)
		return(false);
	if (map[row][col] == ' ' || map[row][col] == '\t')
		return(false);
	if (map[row][col] == '1' || map[row][col] == 'V')
		return(true);
	map[row][col] = 'V';
	if (!flood_fill(map, row + 1, col, rowcols))
		return(false);
	if (!flood_fill(map, row - 1, col, rowcols))
		return(false);
	if (!flood_fill(map, row, col + 1, rowcols))
		return(false);
	if (!flood_fill(map, row, col - 1, rowcols))
		return(false);
	return(true);
}

bool	validate_map(t_map *map)
{
	int bi;
	int si;
	t_rowcols rowcols;
	char **copy;
	
	if (!valid_chars(map->rmap))
		return(false);
	map->max_width = get_max_width(map->rmap);
	copy = pad_map(map->rmap, map->size, map->max_width);
	rowcols.cols = map->max_width;
	rowcols.rows = map->size;
	if (!copy)
		return(false);
	bi = 0;
	while (copy[bi])
	{
		si = 0;
		while (copy[bi][si])
		{
			if (ft_strchr("NSEW", copy[bi][si]))
			{
				if (!flood_fill(copy, bi, si, rowcols))
					error_exit(2);
				free_map(copy, map->size);
				return(true);
			}
			si++;
		}
		bi++;
	}
	error_exit(2);
	return(false);
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


