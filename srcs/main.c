/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:35 by MP9               #+#    #+#             */
/*   Updated: 2026/06/10 23:21:06 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int error_exit(int num)
{
	if (num == 1)
		printf("hey, wrong RGB values mannn\n");
	if (num == 2)
		printf("hey, wrong map mannn\n");
	exit(0);
}

int get_rgb(char **part)
{
	int color;
	int r;
	int g;
	int b;
	
	r = ft_atoi(part[0]);
	g = ft_atoi(part[1]);
	b = ft_atoi(part[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return(error_exit(1));
	color = (r << 16 | g << 8 | b);
	return(color);
}

void assign_colors(t_colors *colors, char *floor, char *ceiling)
{
	char **chao;
	char **teto;

	chao = ft_split(floor, ',');
	teto = ft_split(ceiling, ',');
	colors->ceiling = get_rgb(teto);
	colors->floor = get_rgb(chao);
}

void readfile(int fd, t_parsing *parsing)
{
	int i = 0;

	while (1)
	{
		parsing->lines = get_next_line(fd);
		if (!parsing->lines)
			break;
		if (i >= 0 && i <= 1)
		{
			if (*parsing->lines == 'F')
				parsing->floor = ft_split(parsing->lines, ' ');
			else if (*parsing->lines == 'C')
				parsing->ceiling = ft_split(parsing->lines, ' ');
			parsing->lines = get_next_line(fd);
			if (!parsing->lines)
				break;
			i++;
			if (*parsing->lines == 'C')
				parsing->ceiling = ft_split(parsing->lines, ' ');
			else if (*parsing->lines == 'F')
				parsing->floor = ft_split(parsing->lines, ' ');
			i++;
		}
		if (ft_isalnum(*parsing->lines))
			parsing->maplen++;
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		exit(1);
	int fd = open(argv[1], O_RDONLY);
	if (fd < 3)
		exit(1);
	t_parsing *parsing = malloc(sizeof(t_parsing));
	readfile(fd, parsing);
	close(fd);
	int real_mapi = 0;
	t_colors *colors = malloc((sizeof(t_colors)));
	assign_colors(colors, parsing->floor[1], parsing->ceiling[1]);
	printf("%d\n", colors->ceiling);
	printf("%d\n", colors->floor);
	parsing->map = malloc(sizeof(char *) * (parsing->maplen + 1));
	int mapi = 0;
	fd = open(argv[1], O_RDONLY);
	while (1)
	{
		parsing->lines = get_next_line(fd);
		if (!parsing->lines)
			break;
		if (ft_isdigit(parsing->lines[0]))
		{
			parsing->map[mapi] = parsing->lines;
			mapi++;
		}
	}
	printf("I'm here1\n");
	if (real_mapi > mapi)
		return(error_exit(2));
	for (int i = 0; i < mapi; i++)
		printf("%s", parsing->map[i]);
	close(fd);
	exit(0);
}
