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
	mlx_load_png(textures->north);
	mlx_load_png(textures->south);
	mlx_load_png(textures->east);
	mlx_load_png(textures->west);
}
