/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:07 by MP9               #+#    #+#             */
/*   Updated: 2026/07/15 12:54:23 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# define _GNU_SOURCE

# define WIDTH 800
# define HEIGHT 600

# define TILE 32
# define MINIMAP_PADDING 24
# define MINIMAP_BG 0x202020FF
# define MINIMAP_WALL 0xE0E0E0FF
# define MINIMAP_FLOOR 0x101010FF
# define MINIMAP_VOID 0x050505FF
# define MINIMAP_TILE 8
# define MINIMAP_RADIUS 10

# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define RED   0xFF0000FF
# define GREEN 0x00FF00FF
# define BLUE  0x0000FFFF

# define NPC_SPEED 0.04
# define NPC_RECOMPUTE 0.2
# define NPC_CATCH_DIST 0.4

# define HUD_ICON_SIZE 28
# define HUD_ICON_GAP 6
# define HUD_MARGIN 16
# define HUD_DOT_COLOR 0x808080FF

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
uint32_t	get_rgb(char **part);
void free_map(char **map, int size);
char	*ft_linedup(const char *s1);
void kill_n(char *str);
int	get_max_width(char **map);
char	**pad_map(char **map, int rows, int max_width);
bool flood_fill(char **map, int row, int col, t_rowcols rowcols);
bool is_valid(char a);
bool valid_chars(char **map);
bool	validate_map(t_map *map);
void	get_image(t_game *game, t_cub *cub);
mlx_t *init_window(t_cub *cub);
void draw_tile(mlx_image_t *img, int start_x, int start_y, int size, uint32_t color);
char **deep_copy_map(t_map *map);
void render_map(mlx_image_t *img, t_cub *cub);
void	redraw(t_game *game);
void	resize_hook(int32_t width, int32_t height, void *param);
int error_exit(int num);
void readfile(t_parsing *parsing);
void rf_helper(t_parsing *parsing, int *capacity, int i);
int space_skip(char *str);
void add_wall_textures(t_textures *textures);
t_player	*init_player(t_map *map);
int	is_wall(t_map *map, int x, int y);
void	cast_ray(t_player *player, t_map *map, t_ray *ray, double camera_x);
void	render_frame(void *param);
void	update_player(void *param);
t_npc	*init_npc(t_map *map);
void	update_npc(void *param);
void	draw_npc(mlx_image_t *img, t_cub *cub);
void	draw_sprite(t_cub *cub, double *raycaster_buffer);
void	draw_column(t_cub *cub, t_ray *ray, int x);
uint32_t	tex_pixel_color(mlx_texture_t *tex, int tex_x, int tex_y);
void	draw_billboard_sprite(t_cub *cub, t_dpoint pos,
			mlx_texture_t *tex, double *raycaster_buffer);
void	update_items(void *param);
int		count_total_cans(t_map *map);
void	draw_cans(t_cub *cub, double *raycaster_buffer);
void	draw_can_hud(t_cub *cub);

#endif
