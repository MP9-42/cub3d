/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:07 by MP9               #+#    #+#             */
/*   Updated: 2026/06/13 14:36:48 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define _GNU_SOURCE

# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h> 
# include <stdio.h>
# include <limits.h>
# include "get_next_line.h"
# include "libft.h"
# include "structs.h"

t_colors *assign_colors(char *floor, char *ceiling);
int get_rgb(char **part);
bool is_valid(char a);
bool is_correct(char **map);
int error_exit(int num);
int space_skip(char *str);

#endif