/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:07 by MP9               #+#    #+#             */
/*   Updated: 2026/06/23 17:45:10 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define _GNU_SOURCE

# define WIDTH 800
# define HEIGHT 600
# define TILE 32

# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define RED   0xFF0000FF
# define GREEN 0x00FF00FF

# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include "get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
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
void	redraw(t_game *game);
bool	validate_map(t_map *map);
void	get_image(t_game *game, t_cub *cub);
mlx_t *init_window(t_cub *cub);
void draw_tile(mlx_image_t *img, int start_x, int start_y, int size, uint32_t color);
char **deep_copy_map(t_map *map);
void render_map(mlx_image_t *img, t_cub *cub);
int error_exit(int num);
void	resize_hook(int32_t width, int32_t height, void *param);
void readfile(t_parsing *parsing);
void rf_helper(t_parsing *parsing, int *capacity, int i);
int space_skip(char *str);
t_player	*init_player(t_map *map);
void		cast_ray(t_player *player, t_map *map, t_ray *ray, double camera_x);

#endif
