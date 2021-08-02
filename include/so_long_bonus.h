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

enum	e_p_direciton
{
	FRONT,
	LEFT,
	RIGHT,
	BACK,
	NUM
};

enum	e_p_action
{
	ACTION1,
	ACTION2
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
	void	*player_img[4][2];
	void	*tile_img;
	void	*wall_img;
	void	*exit_img;
	void	*collectible_img;
	void	*gray_img;
	void	*p_exit;
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
	int		action;
	bool	err;
	bool	end;
	t_point	p_pos;
	t_img	img;
}	t_vars;

void	read_map(t_vars *vars, char *map_name);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	init_vars(t_vars *vars);
int		destroy_and_exit(t_vars *vars);
int		key_hook(int key_code, t_vars *vars);
int		check_map(t_vars *vars);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
void	put_back_gray(t_vars *vars);
void	put_info_to_window(t_vars *vars);

#endif