/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:16 by MP9               #+#    #+#             */
/*   Updated: 2026/06/12 20:43:52 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


typedef struct s_colors t_colors;
typedef struct s_map t_map;
typedef struct s_textures t_textures;
typedef struct s_cub t_cub;
typedef struct s_parsing t_parsing;

typedef struct s_textures
{
	char *north;
	char *south;
	char *west;
	char *east;
}				t_textures;

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
	char **rmap;
	int		size;
}				t_map;

typedef struct s_cub
{
	t_parsing	*parsing;
	t_textures *textures;
	t_colors	*colors;
	t_map		**map;
	int			*fd;								//bro vertrau wir machen eif multiple maps mit den fds damit man mehrere lvl hat, die man ohne exiten starten kann;
}				t_cub;