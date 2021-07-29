#ifndef SO_LONG_H
# define SO_LONG_H
// # define W 119
// # define A 97
// # define S 115
// # define D 100
// # define ESC 65307
# define TILE_SIZE 60
# define PLAYER_IMG "./img_src/player4.xpm"
# define TILE_IMG "./img_src/tile2.xpm"
# define COLLECTIBLE_IMG "./img_src/collectible.xpm"
# define WALL_IMG "./img_src/wall.xpm"
# define EXIT_IMG "./img_src/exit2.xpm"
#ifdef __linux__
# include "../mlx-linux/mlx.h"
#define K_W 119
#define K_A 97
#define K_S 115
#define K_D 100
#define K_ESC 65307
// #define IS_LINUX 1
#else
# include "../mlx-mac/mlx.h"
#define K_W 13
#define K_A 0
#define K_S 1
#define K_D 2
#define K_ESC 53
// #define IS_LINUX 0
void mlx_destroy_display(void *ptr);
#endif

# include "../get_next_line/get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
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

typedef struct s_img
{
	void	*player_img;
	void	*tile_img;
	void	*wall_img;
	void	*exit_img;
	void	*collectible_img;
}	t_img;

typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
	char	**map;
	int		map_height;
	int		map_width;
	int		collectible;
	int		collected;
	int		step_cnt;
	bool	err;
	t_point	p_pos;
	t_img	img;
}	t_vars;

void	read_map(t_vars *vars, char *map_name);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	init_vars(t_vars *vars);
int		destroy_and_exit(t_vars *vars);
int		loop_draw(t_vars *vars);
int		key_hook(int key_code, t_vars *vars);
int		check_map(t_vars *vars);

#endif