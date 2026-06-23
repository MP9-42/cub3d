/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:16 by MP9               #+#    #+#             */
/*   Updated: 2026/06/23 15:01:32 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


typedef struct s_colors t_colors;
typedef struct s_map t_map;
typedef struct s_textures t_textures;
typedef struct s_cub t_cub;
typedef struct s_rowcols t_rowcols;
typedef struct s_parsing t_parsing;
typedef struct s_game t_game;
typedef struct s_player t_player;
typedef struct s_ray t_ray;
typedef struct s_window t_window;


typedef struct s_window
{
	void	*win;
	int32_t height;
	int32_t width;
	int32_t tilesize;
}				t_window;

typedef struct s_textures
{
	char *north;
	char *south;
	char *west;
	char *east;
}				t_textures;

typedef struct s_rowcols
{
	int rows;
	int cols;
}				t_rowcols;

typedef struct s_game
{
	mlx_t		*mlx;
	t_window	*window;
	mlx_image_t *img;
	t_player	*player;
}				t_game;

typedef struct s_parsing
{
	int fd;
	int file_len;
	int map_len;
	char **floor;
	char **ceiling;
	char **file;
}				t_parsing;

typedef struct s_colors
{
	int floor;
	int ceiling;
}				t_colors;

typedef struct s_map
{
	char 	**rmap;
	int		size;
	int		max_width;
}				t_map;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

typedef struct s_cub
{
	t_game		*game;
	t_parsing	*parsing;
	t_textures	*textures;
	t_colors	*colors;
	t_map		*map;
	t_player	*player;
	int			*fd;								//bro vertrau wir machen eif multiple maps mit den fds damit man mehrere lvl hat, die man ohne exiten starten kann;
}				t_cub;

typedef struct s_point
{
	int x;
	int y;
}				t_point;
