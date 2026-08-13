/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:07 by MP9               #+#    #+#             */
/*   Updated: 2026/08/13 12:52:17 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define _GNU_SOURCE

# define WIDTH 800
# define HEIGHT 600

# define MINIMAP_PADDING 24
# define MINIMAP_WALL 0xE0E0E0FF
# define MINIMAP_FLOOR 0x101010FF
# define MINIMAP_VOID 0x050505FF
# define MINIMAP_TILE 8
# define MINIMAP_RADIUS 10
# define MINIMAP_FINISH 0x00D050FF
# define MINIMAP_FINISH_LOCKED 0x2E5638FF

/* The finish is a solid wall tile: it only opens once every can has
   been picked up, and the player has to walk up and touch its face. */
# define FINISH_TILE '9'
# define FINISH_TOUCH 0.4
# define FINISH_LOCK_SHADE 3

# define MOUSE_SENS 0.0015

/* TAB freezes the game and hands the cursor back to the window manager
   so the mouse can reach the X button; TAB again re-locks it. */
# define PAUSE_BAR_W 16
# define PAUSE_BAR_H 56
# define PAUSE_BAR_GAP 14
# define PAUSE_DIM 3

# define WHITE 0xFFFFFFFF
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
# include <sys/time.h>
# include "get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include "structs.h"

/* main.c */
void		init_cub(char **argv, t_cub *cub, t_parsing *parsing);

/* errors/errors1.c */
int			error_exit(int num);

/* parsing/parser_utils.c */
int			count_spawns(char **map);
bool		valid_chars(char **map);
char		*ft_linedup(const char *s1);

/* parsing/colors.c */
uint32_t	get_rgb(char **part);
t_colors	*assign_colors(char *floor, char *ceiling);

/* parsing/textures.c */
void		add_wall_textures(t_textures *textures);

/* parsing/map_parse.c */
bool		validate_map(t_map *map);
int			get_max_width(char **map);
char		**pad_map(char **map, int rows, int max_width);

/* map/map_init.c */
void		readfile(t_parsing *parsing);
t_map		*map_allocator(t_parsing *parsing, int *start);
int			map_maker(t_map *map, t_parsing *parsing, int start);

/* map/map_assign.c */
t_map		*get_map(t_cub *cub, t_parsing *parsing);
bool		flood_fill(char **map, int row, int col, t_rowcols rowcols);

/* utils/utils1.c */
bool		is_valid(char a);
int			space_skip(char *str);
void		kill_n(char *str);
void		rf_helper(t_parsing *parsing, int *capacity, int i);

/* utils/utils2.c */
void		free_map(char **map, int size);
void		tab_converter(const char *s1, char *s2, size_t *i, size_t *j);
void		line_cruncher(t_map *map, t_rowcols *rowcols);
char		map_tile(t_map *map, int x, int y);

/* player/player_init.c */
t_player	*init_player(t_map *map);

/* player/player_move.c */
void		update_player(void *param);

/* raycaster/dda.c */
int			is_wall(t_map *map, int x, int y);
void		cast_ray(t_player *player, t_map *map, t_ray *ray, double camera_x);

/* raycaster/render.c */
void		render_frame(void *param);

/* raycaster/render_wall.c */
void		draw_column(t_cub *cub, t_ray *ray, int x);

/* raycaster/render_sprite.c */
uint32_t	tex_pixel_color(mlx_texture_t *tex, int tex_x, int tex_y);
void		draw_billboard_sprite(t_cub *cub, t_dpoint pos,
				mlx_texture_t *tex, double *raycaster_buffer);

/* window/init.c */
void		get_image(t_game *game, t_cub *cub);

/* window/pause.c */
void		draw_pause_overlay(t_cub *cub);
void		toggle_pause(t_cub *cub);
void		key_hook(mlx_key_data_t keydata, void *param);

/* window/minimap.c */
void		draw_tile(mlx_image_t *img, t_point start, int size, uint32_t c);
void		draw_player(mlx_image_t *img, t_cub *cub, int ox, int oy);

/* window/minimap_grid.c */
void		render_map(mlx_image_t *img, t_cub *cub);

/* bonus/police.c */
void		update_npc(void *param);
void		draw_npc(mlx_image_t *img, t_cub *cub);
void		draw_sprite(t_cub *cub, double *raycaster_buffer);

/* bonus/police_init.c */
t_npc		*init_npc(t_map *map);

/* bonus/police_bfs.c */
void		bfs_alloc(t_bfs *bfs);
void		bfs_init(int start_x, int start_y, t_bfs *bfs);
void		breadth_first_search(t_map *map, t_bfs *bfs);

/* bonus/police_path.c */
int			bifis(t_map *map, t_bfs *bfs);

/* bonus/police_chase.c */
double		get_time(void);
void		get_length(t_cub *cub, t_npc *npc, t_bfs *bfs, double now);
void		get_distance(t_cub *cub, t_npc *npc, t_bfs *bfs);
void		move_n_get_distance(t_cub *cub, t_npc *npc, t_bfs *bfs);

/* bonus/items.c */
void		update_items(void *param);
int			count_total_cans(t_map *map);
void		draw_cans(t_cub *cub, double *raycaster_buffer);

/* bonus/items_hud.c */
void		draw_can_hud(t_cub *cub);

/* bonus/finish.c */
bool		finish_unlocked(t_cub *cub);
bool		is_finish_hit(t_cub *cub, t_ray *ray);
bool		touching_finish(t_cub *cub);
void		check_finish(t_cub *cub);
uint32_t	wall_pixel(t_cub *cub, mlx_texture_t *tex, int tx, int ty);

#endif
