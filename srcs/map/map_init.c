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

static int	find_map_start(char **file)
{
	int		i;

	i = 0;
	while (file[i])
	{
		if (line_starts_map(file[i]))
			return (i);
		i++;
	}
	return (-1);
}

t_map	*map_allocator(t_parsing *parsing)
{
	int		i;
	int		count;
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		return (error_exit(2), NULL);
	map->start = find_map_start(parsing->file);
	if (map->start < 0)
		return (error_exit(2), NULL);
	count = 0;
	i = map->start;
	while (parsing->file[i])
	{
		if (line_starts_map(parsing->file[i]))
			count++;
		i++;
	}
	if (count <= 0)
		return (error_exit(2), NULL);
	map->rmap = malloc(sizeof(char *) * (count + 1));
	if (!map->rmap)
		return (error_exit(2), NULL);
	map->count = count;
	return (map);
}
