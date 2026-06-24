/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 13:40:43 by MP9               #+#    #+#             */
/*   Updated: 2026/06/24 14:06:57 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

uint32_t	get_rgb(char **part)
{
	int r;
	int g;
	int b;

	r = ft_atoi(part[0]);
	g = ft_atoi(part[1]);
	b = ft_atoi(part[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (error_exit(1));
	return ((uint32_t)r << 24 | (uint32_t)g << 16 | (uint32_t)b << 8 | 0xFF);
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
