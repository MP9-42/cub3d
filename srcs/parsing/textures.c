/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:49:44 by MP9               #+#    #+#             */
/*   Updated: 2026/08/12 16:04:49 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// adds textures from our .cub file and exits if any of them fail to load
void	add_wall_textures(t_textures *textures)
{
	textures->north_tex = mlx_load_png(textures->north);
	textures->south_tex = mlx_load_png(textures->south);
	textures->east_tex = mlx_load_png(textures->east);
	textures->west_tex = mlx_load_png(textures->west);
	textures->police_tex = mlx_load_png("textures/sprites/POLICE.png");
	textures->can_tex = mlx_load_png("textures/sprites/BLUE.png");
	textures->finish_tex = mlx_load_png("textures/FINISH_TEX.png");
	if (!textures->north_tex || !textures->south_tex
		|| !textures->east_tex || !textures->west_tex
		|| !textures->police_tex || !textures->can_tex
		|| !textures->finish_tex)
	{
		ft_putstr_fd("Error\nFailed to load textures\n", 2);
		exit(1);
	}
}
