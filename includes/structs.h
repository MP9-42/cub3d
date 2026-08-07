/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:16 by MP9               #+#    #+#             */
/*   Updated: 2026/07/22 16:03:18 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

# define MAX_PATH 1024

typedef struct s_colors		t_colors;
typedef struct s_map		t_map;
typedef struct s_textures	t_textures;
typedef struct s_cub		t_cub;
typedef struct s_rowcols	t_rowcols;
typedef struct s_parsing	t_parsing;
typedef struct s_game		t_game;
typedef struct s_player		t_player;
typedef struct s_npc		t_npc;
typedef struct s_ray		t_ray;
typedef enum e_tiletype		t_tyletype;

typedef struct s_bfs
{
	double			now;
	double			target_x;
	double			target_y;
	double			dist;
	int				*visited;
	int				*par_x;
	int				*par_y;
	int				*path_x;
	int				*path_y;
	int				*queue_x;
	int				*queue_y;
	int				front;
	int				start_x;
	int				start_y;
	int				rear;
	int				dx[4];
	int				dy[4];
	int				i;
	int				end_x;
	int				end_y;
	int				player_tile_x;
	int				player_tile_y;
	int				nx;
	int				ny;
	int				current_x;
	int				current_y;
	int				len;
	int				idx;
	int				width;
	int				total;
}					t_bfs;

typedef struct s_textures
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*police;
	char			*can;
	mlx_texture_t	*police_tex;
	mlx_texture_t	*can_tex;
	mlx_texture_t	*north_tex;
	mlx_texture_t	*south_tex;
	mlx_texture_t	*west_tex;
	mlx_texture_t	*east_tex;
}					t_textures;

typedef struct s_rowcols
{
	int				rows;
	int				cols;
	bool			value;
	char			**padded;
	char			**copy;
}					t_rowcols;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		*player;
	t_cub			*cub;
	int32_t			width;
	int32_t			height;
}					t_game;

typedef enum e_tiletype
{
	POLICE = 6,
	CAN = 7,
	ELEVATOR = 8,
	FINISH = 9,
}					t_tyletype;

typedef struct s_parsing
{
	int				fd;
	int				file_len;
	int				map_len;
	char			**floor;
	char			**ceiling;
	char			**file;
}					t_parsing;

typedef struct s_colors
{
	uint32_t		floor;
	uint32_t		ceiling;
}					t_colors;

typedef struct s_map
{
	char			**rmap;
	int				size;
	int				max_width;
}					t_map;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_ray
{
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	double			perp_wall_dist;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct s_npc
{
	double			dx;
	double			dy;
	double			pos_x;
	double			pos_y;
	double			speed;
	double			last_path_time;
	int				path_x[MAX_PATH];
	int				path_y[MAX_PATH];
	int				path_length;
	int				current_target;
	int				offset_x;
	int				offset_y;
	int				screen_x;
	int				screen_y;
	int				view;
	int				minimap_x;
	int				minimap_y;
	int				ps;
	bool			active;
}					t_npc;

typedef struct s_cub
{
	t_game			*game;
	t_parsing		*parsing;
	t_textures		*textures;
	t_colors		*colors;
	t_map			*map;
	t_player		*player;
	t_npc			*npc;
	int				*fd;
	int				can_count;
	int				total_cans;
	bool			game_over;
	bool			you_win;
	bool			overlay_drawn;
}					t_cub;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_dpoint
{
	double			x;
	double			y;
}					t_dpoint;

typedef struct s_sprite
{
	mlx_texture_t	*tex;
	double			transform_x;
	double			transform_y;
	int				screen_x;
	int				height;
	int				width;
	int				start_x;
	int				end_x;
	int				start_y;
	int				end_y;
}					t_sprite;

#endif
