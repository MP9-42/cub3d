/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:35 by MP9               #+#    #+#             */
/*   Updated: 2026/06/19 15:50:02 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int line_starts_map(char *line)
{
	int i;

	if (!line)
		return (0);
	i = space_skip(line);
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	return (is_valid(line[i]) && line[i] != ' ');
}

static char *find_config_value(char **file, char id)
{
	char **parts;
	char *value;
	int i;
	int j;
	int si;

	i = 0;
	while (file[i] && !line_starts_map(file[i]))
	{
		si = space_skip(file[i]);
		if (file[i][si] == id)
		{
			parts = ft_split(file[i], ' ');
			if (!parts || !parts[1])
				return (NULL);
			value = ft_strdup(parts[1]);
			j = 0;
			while (parts[j])
			{
				free(parts[j]);
				j++;
			}
			free(parts);
			return (value);
		}
		i++;
	}
	return (NULL);
}

static int find_map_start(char **file)
{
	int i;

	i = 0;
	while (file[i])
	{
		if (line_starts_map(file[i]))
			return (i);
		i++;
	}
	return (-1);
}

void rf_helper(t_parsing *parsing, int *capacity, int i)
{
	char **new_file;
	int j;

	if (i < *capacity)
		return;
	if (*capacity > INT_MAX / 2)
		return;
	*capacity *= 2;
	new_file = malloc(sizeof(char *) * (*capacity + 1));
	if (!new_file)
		return;
	j = 0;
	while (j < i)
	{
		new_file[j] = parsing->file[j];
		j++;
	}
	new_file[i] = NULL;
	free(parsing->file);
	parsing->file = new_file;
}

void readfile(t_parsing *parsing)
{
	int capacity;
	int i;

	capacity = 16;
	i = 0;
	parsing->file = malloc(sizeof(char *) * (capacity + 1));
	if (!parsing->file)
		return;
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
			break;
		i++;
	}
	parsing->file[i] = NULL;
}

t_map *get_map(t_cub *cub, t_parsing *parsing)
{
	t_map *map;
	char *floor;
	char *ceiling;
	int count;
	int mi;
	int start;
	int i;

	if (!cub || !parsing || !parsing->file)
		return (error_exit(2), NULL);
	floor = find_config_value(parsing->file, 'F');
	ceiling = find_config_value(parsing->file, 'C');
	if (!floor || !ceiling)
		return (error_exit(2), NULL);
	cub->colors = assign_colors(floor, ceiling);
	free(floor);
	free(ceiling);
	start = find_map_start(parsing->file);
	if (start < 0)
		return (error_exit(2), NULL);
	count = 0;
	i = start;
	while (parsing->file[i] && line_starts_map(parsing->file[i]))
	{
		count++;
		i++;
	}
	if (count <= 0)
		return (error_exit(2), NULL);
	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		return (error_exit(2), NULL);
	map->rmap = malloc(sizeof(char *) * (count + 1));
	if (!map->rmap)
		return (error_exit(2), NULL);
	map->size = count;
	mi = 0;
	i = start;
	while (mi < count)
	{
		map->rmap[mi] = ft_linedup(parsing->file[i]);
		if (!map->rmap[mi])
			return (error_exit(2), NULL);
		kill_n(map->rmap[mi]);
		mi++;
		i++;
	}
	map->rmap[count] = NULL;
	return (map);
}

int main(int argc, char **argv)
{
	t_cub *cub;
	t_parsing *parsing;

	if (argc != 2)
		exit(1);
	cub = ft_calloc(sizeof(t_cub), 1);
	parsing = ft_calloc(1, sizeof(t_parsing));
	if (!cub || !parsing)
		exit(1);
	parsing->fd = open(argv[1], O_RDONLY);
	if (parsing->fd < 0)
		exit(1);
	readfile(parsing);
	if (!parsing->file)
		exit(1);
	parsing->file_len = 0;
	while (parsing->file[parsing->file_len])
		parsing->file_len++;
	cub->parsing = parsing;
	cub->map = get_map(cub, parsing);
	if (!validate_map(cub->map))
		error_exit(2);
	for (int i = 0; cub->map->rmap[i] ; i++)
		printf("%s\n", cub->map->rmap[i]);
	close(parsing->fd);
	exit(0);
}
