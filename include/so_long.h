#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx-linux/mlx.h"
#include <stdio.h>

typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
	void	*player_img;
	void	*tile_img;
}	t_vars;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

#endif