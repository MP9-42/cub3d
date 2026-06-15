/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 13:40:43 by MP9               #+#    #+#             */
/*   Updated: 2026/06/15 19:06:13 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

t_colors *assign_colors(char *floor, char *ceiling)
{
	char **chao;
	char **teto;
	t_colors *colors;

	colors = ft_calloc(sizeof(t_colors), 1);
	chao = ft_split(floor, ',');
	teto = ft_split(ceiling, ',');
	colors->ceiling = get_rgb(teto);
	colors->floor = get_rgb(chao);
	return(colors);
}
