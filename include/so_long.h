#ifndef SO_LONG_H
# define SO_LONG_H
# define W 119
# define A 97
# define S 115
# define D 100
# define player_img_path "./player4.xpm"
# define tile_img_path "./tile2.xpm"
# define collectible_img_path "./collectible.xpm"

# include "../mlx-linux/mlx.h"
# include "../get_next_line/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
#include <stdio.h>

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
	void	*player_img;
	void	*tile_img;
	void	*collectible_img;
	char	**map;
	int		map_height;
	int		map_width;
	t_point	player_point;
}	t_vars;


#endif