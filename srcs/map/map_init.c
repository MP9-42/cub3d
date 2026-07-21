/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 19:25:05 by MP9               #+#    #+#             */
/*   Updated: 2026/07/21 19:26:24 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void add_n_assign_textures(t_cub *cub, t_parsing *parsing)
{
	cub->textures = ft_calloc(sizeof(t_textures), 1);
	cub->textures->east = find_config_value(parsing->file, "EA");
	cub->textures->south = find_config_value(parsing->file, "SO");
	cub->textures->north = find_config_value(parsing->file, "NO");
	cub->textures->west = find_config_value(parsing->file, "WE");
	if (cub->textures->east)
		kill_n(cub->textures->east);
	if (cub->textures->south)
		kill_n(cub->textures->south);
	if (cub->textures->north)
		kill_n(cub->textures->north);
	if (cub->textures->west)
		kill_n(cub->textures->west);
	if (cub->textures->police)
		kill_n(cub->textures->police);
	if (cub->textures->can)
		kill_n(cub->textures->can);
	add_wall_textures(cub->textures);
}
