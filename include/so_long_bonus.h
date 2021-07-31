#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../get_next_line/get_next_line.h"
# include "../mlx-linux/mlx.h"
# include "./bonus_define.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

enum	e_player_img
{
	FRONT1,
	FRONT2,
	LEFT1,
	LEFT2,
	RIGHT1,
	RIGHT2,
	BACK1,
	BACK2,
	NUM
};

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
	void	*player_img[NUM];
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
	int		direction;
	bool	err;
	t_point	p_pos;
	t_img	img;
}	t_vars;

void 	read_map(t_vars *vars, char *map_name);
void 	ft_putstr_fd(char *s, int fd);
void 	ft_putnbr_fd(int n, int fd);
void 	init_vars(t_vars *vars);
int 	destroy_and_exit(t_vars *vars);
// int 	loop_draw(t_vars *vars);
int 	key_hook(int key_code, t_vars *vars);
int 	check_map(t_vars *vars);

#endif