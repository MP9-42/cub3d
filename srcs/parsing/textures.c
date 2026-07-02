/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:49:44 by MP9               #+#    #+#             */
/*   Updated: 2026/06/19 21:07:40 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void add_wall_textures(t_textures *textures)
{
	textures->north_tex = mlx_load_png(textures->north);
	textures->south_tex = mlx_load_png(textures->south);
	textures->east_tex = mlx_load_png(textures->east);
	textures->west_tex = mlx_load_png(textures->west);
	if (!textures->north_tex || !textures->south_tex
		|| !textures->east_tex || !textures->west_tex)
	{
		printf("Error\nFailed to load wall textures\n");
		exit(1);
	}
}
