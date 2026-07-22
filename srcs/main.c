/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:35 by MP9               #+#    #+#             */
/*   Updated: 2026/07/22 14:39:25 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*get_value(char **file, char **parts, int i, int j)
{
	char	*value;

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
	return (value);
}

int	map_maker(t_map *map, t_parsing *parsing)
{
	int	i;
	int	mi;

	map->size = map->count;
	mi = 0;
	i = map->start;
	while (mi < map->count)
	{
		map->rmap[mi] = ft_linedup(parsing->file[i]);
		if (!map->rmap[mi])
			return (error_exit(2), 0);
		kill_n(map->rmap[mi]);
		mi++;
		i++;
	}
	map->rmap[map->count] = NULL;
	return(1);
}

bool	init_cub(char **argv, t_cub *cub, t_parsing *parsing, int *value)
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
	*value = 0;
	return (false);
}

void	mlx_loops(t_cub *cub)
{
	get_image(cub->game, cub);
	mlx_loop_hook(cub->game->mlx, update_player, cub);
	mlx_loop_hook(cub->game->mlx, update_npc, cub);
	mlx_loop_hook(cub->game->mlx, update_items, cub);
	mlx_loop_hook(cub->game->mlx, render_frame, cub);
}

int	main(int argc, char **argv)
{
	t_cub		*cub;
	t_parsing	*parsing;
	int			value;

	if (argc != 2)
		exit(1);
	cub = ft_calloc(sizeof(t_cub), 1);
	parsing = ft_calloc(1, sizeof(t_parsing));
	if (!cub || !parsing)
		exit(1);
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
