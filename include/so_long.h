#ifndef SO_LONG_H
# define SO_LONG_H
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define TILE_SIZE 60
# define PLAYER_IMG_PATH "./img_src/player4.xpm"
# define TILE_IMG_PATH "./img_src/tile2.xpm"
# define COLLECTIBLE_IMG_PATH "./img_src/collectible.xpm"
# define WALL_IMG_PATH "./img_src/wall.xpm"
# define EXIT_IMG_PATH "./img_src/exit.xpm"

# include "../mlx-linux/mlx.h"
# include "../get_next_line/get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_ischr
{
	int	cnt_player;
	int	cnt_exit;
}	t_cntchr;

typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
	void	*player_img;
	void	*tile_img;
	void	*wall_img;
	void	*exit_img;
	void	*collectible_img;
	char	**map;
	int		map_height;
	int		map_width;
	t_point	player_point;
	int		collectible;
	int		collected;
	int		step_cnt;
}	t_vars;

#endif