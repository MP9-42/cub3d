/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 13:44:51 by MP9               #+#    #+#             */
/*   Updated: 2026/06/11 13:45:31 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int error_exit(int num)
{
	if (num == 1)
		printf("hey, wrong RGB values mannn\n");
	if (num == 2)
		printf("hey, wrong map mannn\n");
	exit(0);
}

