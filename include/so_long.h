#ifndef SO_LONG_H
# define SO_LONG_H
# define W 119
# define A 97
# define S 115
# define D 100

# include "../mlx-linux/mlx.h"
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
	t_point	player_point;
}	t_vars;


#endif