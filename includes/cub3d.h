/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:07 by MP9               #+#    #+#             */
/*   Updated: 2026/06/17 14:31:43 by MP9              ###   ########.fr       */
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
void free_map(char **map, int size);
char	*ft_linedup(const char *s1);
void kill_n(char *str);
int	get_max_width(char **map);
char	**pad_map(char **map, int rows, int max_width);
bool flood_fill(char **map, int row, int col, t_rowcols rowcols);
bool is_valid(char a);
bool valid_chars(char **map);
bool	validate_map(t_map *map);
char **deep_copy_map(t_map *map);
int error_exit(int num);
void readfile(t_parsing *parsing);
void rf_helper(t_parsing *parsing, int *capacity, int i);
int space_skip(char *str);

#endif