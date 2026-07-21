/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:35 by MP9               #+#    #+#             */
/*   Updated: 2026/07/21 19:34:40 by MP9              ###   ########.fr       */
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

char *get_value(char **file, char **parts, int i, int j)
{
	char *value;

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
	return value;
}

static char *find_config_value(char **file, char *id)
{
	char **parts;
	char *value;
	int i;
	int j;
	int si;

	i = 0;
	while (file[i])
	{
		si = space_skip(file[i]);
		if (ft_strncmp(file[i] + si, id, ft_strlen(id)) == 0)
		{
			value = get_value(file, parts, i, j);
			if (!value)
				return (error_exit(2), NULL);
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

t_map *get_map(t_cub *cub, t_parsing *parsing)
{
	t_map *map;
	char *floor;
	char *ceiling;
	int count;

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
	map_allocator(map, parsing);
	map_maker(map, parsing);
	return (map);
}

int map_maker(t_map *map, t_parsing *parsing)
{
	int i;
	int mi;

	map->size = map->count;
	mi = 0;
	i = map->start;
	while (mi < map->count)
	{
		map->rmap[mi] = ft_linedup(parsing->file[i]);
		if (!map->rmap[mi])
			return (error_exit(2), NULL);
		kill_n(map->rmap[mi]);
		mi++;
		i++;
	}
	map->rmap[map->count] = NULL;
}
int map_allocator(t_map *map, t_parsing *parsing)
{
	int i;
	int count;

	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		return (error_exit(2), 0);
	map->start = find_map_start(parsing->file);
	if (map->start < 0)
		return (error_exit(2), 0);
	count = 0;
	i = map->start;
	while (parsing->file[i] && line_starts_map(parsing->file[i]))
	{
		count++;
		i++;
	}
	if (count <= 0)
		return (error_exit(2), 0);
	map->rmap = malloc(sizeof(char *) * (count + 1));
	if (!map->rmap)
		return (error_exit(2), 0);
	map->count = count;
}

bool init_cub(char **argv, t_cub *cub, t_parsing *parsing, int *value)
{
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
	cub->total_cans = count_total_cans(cub->map);
	cub->game = ft_calloc(sizeof(t_game), 1);
	cub->player = init_player(cub->map);
	cub->npc = init_npc(cub->map);
	cub->game->width = WIDTH;
	cub->game->height = HEIGHT;
	cub->game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	return false;
}

void mlx_loops(t_cub *cub)
{
	get_image(cub->game, cub);
	mlx_loop_hook(cub->game->mlx, update_player, cub);
	mlx_loop_hook(cub->game->mlx, update_npc, cub);
	mlx_loop_hook(cub->game->mlx, update_items, cub);
	mlx_loop_hook(cub->game->mlx, render_frame, cub);
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
	int value;
	if (init_cub(argv, cub, parsing, &value))
		exit(value);
	if (!cub->game->mlx)
		exit(1);
	cub->game->player = cub->player;
	cub->game->cub = cub;
	mlx_loops(cub);
	close(parsing->fd);
	mlx_loop(cub->game->mlx);
	mlx_terminate(cub->game->mlx);
	exit(0);
}
