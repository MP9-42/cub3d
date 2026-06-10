#include "cub3d.h"


typedef struct s_colors t_colors;
typedef struct s_textures t_textures;
typedef struct s_cub t_cub;

typedef struct s_textures
{
	char *north;
	char *south;
	char *west;
	char *east;
}				t_textures;

typedef struct s_colors
{
	int floor;
	int ceiling;
}				t_colors;

typedef struct s_cub
{
	t_textures *textures;
	t_colors	*colors;
	char		**map;
	

}				t_cub;