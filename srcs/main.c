/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:35 by MP9               #+#    #+#             */
/*   Updated: 2026/06/11 18:31:13 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void readfile(int fd, t_parsing *parsing)
{
	int i = 0;
	int index = 0;

	while (1)
	{
		parsing->line = get_next_line(fd);
		if (!parsing->line)
			break;
		if (i >= 0 && i <= 1)
		{
			if (*parsing->line == 'F')
				parsing->floor = ft_split(parsing->line, ' ');
			else if (*parsing->line == 'C')
				parsing->ceiling = ft_split(parsing->line, ' ');
			free(parsing->line);
			parsing->line = get_next_line(fd);
			if (!parsing->line)
				break;
			i++;
			if (*parsing->line == 'C')
				parsing->ceiling = ft_split(parsing->line, ' ');
			else if (*parsing->line == 'F')
				parsing->floor = ft_split(parsing->line, ' ');
			i++;
		}
		index = space_skip(parsing->line);
		if (is_valid(parsing->line[index]) || zisvalid(parsing->line[ft_strlen(parsing->line)]))
			parsing->map_len++;
		parsing->file_len++;
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		exit(1);
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit(1);
	t_parsing *parsing = ft_calloc(1, sizeof(t_parsing));
	readfile(fd, parsing);
	close(fd);
	t_colors *colors = malloc((sizeof(t_colors)));
	assign_colors(colors, parsing->floor[1], parsing->ceiling[1]);
	parsing->file = malloc(sizeof(char *) * (parsing->file_len + 1));
	int fd2 = open(argv[1], O_RDONLY);
	int real_mapi = parsing->file_len;
	int begin = 0;
	int mapi = 0;
	int len = 0;
	fd = open(argv[1], O_RDONLY);
	while (1)
	{
		parsing->line = get_next_line(fd);
		if (!parsing->line)
			break;
		if (parsing->line[begin] == ' ')
			begin = space_skip(&parsing->line[begin]);
		if (ft_isdigit(parsing->line[begin]) && parsing->line[begin] != '\0')
		{
			parsing->file[mapi] = parsing->line;
			len = ft_strlen(parsing->file[mapi]);
			if (parsing->file[mapi][len - 1] == '\n')
				parsing->file[mapi][len - 1] = '\0';
			mapi++;
		}
	}
	parsing->file[mapi] = NULL;
	for (int i = 0; i < mapi; i++)
		printf("%s\n", parsing->file[i]);
	if (real_mapi > mapi)
		return(error_exit(2));
	if (!is_correct(parsing->file))
		return(error_exit(2));
	close(fd);
	exit(0);
}
