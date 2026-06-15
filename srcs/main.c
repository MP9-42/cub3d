/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:35 by MP9               #+#    #+#             */
/*   Updated: 2026/06/13 14:43:42 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void readfile(t_parsing *parsing)
{
	int i = 0;
	int j = 0;
	int len = 15;
	int newlen = 0;
	char	**file;

	while (1)
	{
		if (i == len)
		{
			newlen = len * 2;
			file = malloc(sizeof(char *) * (newlen + 1));
			j = -1;
			while (++j < i)
				file[j] = parsing->file[j];
			if (parsing->file)
				free(parsing->file);
			parsing->file = file;
			len = newlen;		
		}
		parsing->file[i] = get_next_line(parsing->fd);
		if (!parsing->file[i])
			break;			
		i++;
	}
}

t_map *get_map(t_cub *cub, t_parsing *parsing)
{
	t_map *map = ft_calloc(sizeof(t_map), 1);
	char **floor;
	char **ceiling;
	t_colors *colors = assign_colors(floor, ceiling); 
	
	if (parsing->file[0][0] == 'F')
		floor = ft_split(parsing->file[0], ' ');
	else if(parsing->file[0][0] == 'C')
		ceiling = ft_split(parsing->file[0], ' ');
	if (parsing->file[1][0] == 'F')
		floor = ft_split(parsing->file[1], ' ');
	else if(parsing->file[1][0] == 'C')
		ceiling = ft_split(parsing->file[1], ' ');
}

int main(int argc, char **argv)
{
	if (argc != 2)
		exit(1);
	t_cub *cub = ft_calloc(sizeof(t_cub), 1);
	t_parsing *parsing = ft_calloc(1, sizeof(t_parsing));
	parsing->fd = open(argv[1], O_RDONLY);
	parsing->file = ft_calloc(sizeof(char *) , 15 + 1);
	readfile(parsing);
	parsing->file_len = 0;
	while (parsing->file[parsing->file_len])
		parsing->file_len++;
	cub->parsing = parsing;
	for (int i = 0; i < parsing->file_len; i++)
		printf("%s", parsing->file[i]);
	close(parsing->fd);
	// t_colors *colors = malloc((sizeof(t_colors)));
	// assign_colors(colors, parsing->floor[1], parsing->ceiling[1]);
	exit(0);
}
