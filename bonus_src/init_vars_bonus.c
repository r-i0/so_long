#include "../include/so_long_bonus.h"

int	cnt_map_width(t_vars *vars)
{
	int	x;
	int	y;
	int	width;

	y = 0;
	width = 0;
	while (y < vars->map_height)
	{
		x = 0;
		while (vars->map[y][x])
			x++;
		if (width == 0)
			width = x;
		else if (width != x)
		{
			ft_putstr_fd("Error\n", STDERR_FILENO);
			ft_putstr_fd("The map is not rectangular.\n", STDERR_FILENO);
			destroy_and_exit(vars);
		}
		y++;
	}
	return (width);
}

void	set_image(t_vars *vars)
{
	int x;
	int y;

	vars->img.player_img[FRONT1] = mlx_xpm_file_to_image(vars->mlx, P_FRONT1, &x, &y);
	vars->img.player_img[FRONT2] = mlx_xpm_file_to_image(vars->mlx, P_FRONT2, &x, &y);
	vars->img.player_img[LEFT1] = mlx_xpm_file_to_image(vars->mlx, P_LEFT1, &x, &y);
	vars->img.player_img[LEFT2] = mlx_xpm_file_to_image(vars->mlx, P_LEFT2, &x, &y);
	vars->img.player_img[RIGHT1] = mlx_xpm_file_to_image(vars->mlx, P_RIGHT1, &x, &y);
	vars->img.player_img[RIGHT2] = mlx_xpm_file_to_image(vars->mlx, P_RIGHT2, &x, &y);
	vars->img.player_img[BACK1] = mlx_xpm_file_to_image(vars->mlx, P_BACK1, &x, &y);
	vars->img.player_img[BACK2] = mlx_xpm_file_to_image(vars->mlx, P_BACK2, &x, &y);
	vars->img.tile_img = mlx_xpm_file_to_image(vars->mlx, TILE, &x, &y);
	vars->img.collectible_img = mlx_xpm_file_to_image(vars->mlx,
													  COLLECTIBLE, &x, &y);
	vars->img.wall_img = mlx_xpm_file_to_image(vars->mlx, WALL, &x, &y);
	vars->img.exit_img = mlx_xpm_file_to_image(vars->mlx, EXIT, &x, &y);
}

void	init_vars(t_vars *vars)
{
	vars->err = false;
	vars->map_width = cnt_map_width(vars);
	vars->mlx = mlx_init();
	vars->mlx_win = mlx_new_window(vars->mlx, vars->map_width * TILE_SIZE,
			vars->map_height * TILE_SIZE, "so_long");
	set_image(vars);
	// if (!vars->mlx || !vars->mlx_win || !vars->img.tile_img
	// 	|| !vars->img.player_img || !vars->img.collectible_img
	// 	|| !vars->img.wall_img || !vars->img.exit_img)
	// 	destroy_and_exit(vars);
	vars->collectible = 0;
	vars->collected = 0;
	vars->step_cnt = 0;
	vars->direction = FRONT1;
}
