/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_assign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 19:28:08 by MP9               #+#    #+#             */
/*   Updated: 2026/07/22 15:36:36 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*get_value(char **file, int i)
{
	char	**parts;
	char	*value;
	int		j;

	parts = ft_split(file[i], ' ');
	if (!parts || !parts[1])
		return (error_exit(2), NULL);
	value = ft_strdup(parts[1]);
	j = 0;
	while (parts[j])
	{
		free(parts[j]);
		j++;
	}
	free(parts);
	if (value)
		kill_n(value);
	return (value);
}

static char	*find_config_value(char **file, char *id)
{
	char	*value;
	int		i;
	int		si;

	i = 0;
	while (file[i])
	{
		si = space_skip(file[i]);
		if (ft_strncmp(file[i] + si, id, ft_strlen(id)) == 0)
		{
			value = get_value(file, i);
			if (!value)
				return (error_exit(2), NULL);
			return (value);
		}
		i++;
	}
	return (NULL);
}

void	add_n_assign_textures(t_cub *cub, t_parsing *parsing)
{
	cub->textures = ft_calloc(sizeof(t_textures), 1);
	cub->textures->east = find_config_value(parsing->file, "EA");
	cub->textures->south = find_config_value(parsing->file, "SO");
	cub->textures->north = find_config_value(parsing->file, "NO");
	cub->textures->west = find_config_value(parsing->file, "WE");
	if (!cub->textures->east || !cub->textures->south
		|| !cub->textures->north || !cub->textures->west)
		error_exit(2);
	kill_n(cub->textures->east);
	kill_n(cub->textures->south);
	kill_n(cub->textures->north);
	kill_n(cub->textures->west);
	add_wall_textures(cub->textures);
}

t_map	*get_map(t_cub *cub, t_parsing *parsing)
{
	t_map	*map;
	char	*floor;
	char	*ceiling;
	int		start;

	if (!cub || !parsing || !parsing->file)
		return (error_exit(2), NULL);
	add_n_assign_textures(cub, parsing);
	floor = find_config_value(parsing->file, "F");
	ceiling = find_config_value(parsing->file, "C");
	if (!floor || !ceiling)
		return (error_exit(2), NULL);
	cub->colors = assign_colors(floor, ceiling);
	free(floor);
	free(ceiling);
	map = map_allocator(parsing, &start);
	if (!map)
		return (error_exit(2), NULL);
	if (map_maker(map, parsing, start) == 0)
		return (error_exit(2), NULL);
	return (map);
}

bool	flood_fill(char **map, int row, int col, t_rowcols rowcols)
{
	if (row < 0 || col < 0 || row >= rowcols.rows || col >= rowcols.cols)
		return (false);
	if (map[row][col] == ' ' || map[row][col] == '\t')
		return (false);
	if (map[row][col] == '1' || map[row][col] == 'V')
		return (true);
	map[row][col] = 'V';
	if (!flood_fill(map, row + 1, col, rowcols))
		return (false);
	if (!flood_fill(map, row - 1, col, rowcols))
		return (false);
	if (!flood_fill(map, row, col + 1, rowcols))
		return (false);
	if (!flood_fill(map, row, col - 1, rowcols))
		return (false);
	return (true);
}
