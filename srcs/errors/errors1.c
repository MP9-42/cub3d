/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 13:44:51 by MP9               #+#    #+#             */
/*   Updated: 2026/07/22 13:45:40 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	error_exit(int num)
{
	if (num == 1)
		ft_putstr_fd("Error\nInvalid color (need R,G,B in 0-255)\n", 2);
	else if (num == 2)
		ft_putstr_fd("Error\nInvalid map\n", 2);
	else
		ft_putstr_fd("Error\nUsage: ./cub3D <scene.cub>\n", 2);
	exit(1);
}
