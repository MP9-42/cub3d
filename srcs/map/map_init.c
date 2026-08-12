/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 19:25:05 by MP9               #+#    #+#             */
/*   Updated: 2026/07/22 15:51:29 by MP9              ###   ########.fr       */
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

static int	line_starts_map(char *line)
{
	int		i;

	if (!line)
		return (0);
	i = space_skip(line);
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	return (is_valid(line[i]) && line[i] != ' ');
}

static int	is_blank_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = space_skip(line);
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	return (0);
}

static int	is_config_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = space_skip(line);
	if ((ft_strncmp(line + i, "NO", 2) == 0
			&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
		|| (ft_strncmp(line + i, "SO", 2) == 0
			&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
		|| (ft_strncmp(line + i, "WE", 2) == 0
			&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
		|| (ft_strncmp(line + i, "EA", 2) == 0
			&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
		|| (ft_strncmp(line + i, "F", 1) == 0
			&& (line[i + 1] == ' ' || line[i + 1] == '\t'))
		|| (ft_strncmp(line + i, "C", 1) == 0
			&& (line[i + 1] == ' ' || line[i + 1] == '\t')))
		return (1);
	return (0);
}

static int	scan_map(char **file, int *start)
{
	int	i;
	int	count;

	i = 0;
	while (file[i] && !line_starts_map(file[i]))
	{
		if (!is_blank_line(file[i]) && !is_config_line(file[i]))
			error_exit(2);
		i++;
	}
	*start = i;
	count = 0;
	while (file[i] && line_starts_map(file[i]))
	{
		count++;
		i++;
	}
	while (file[i])
	{
		if (!is_blank_line(file[i]))
			error_exit(2);
		i++;
	}
	return (count);
}

t_map	*map_allocator(t_parsing *parsing, int *start)
{
	int		count;
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		return (error_exit(2), NULL);
	count = scan_map(parsing->file, start);
	if (count <= 0)
		return (error_exit(2), NULL);
	map->rmap = malloc(sizeof(char *) * (count + 1));
	if (!map->rmap)
		return (error_exit(2), NULL);
	map->size = count;
	return (map);
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
