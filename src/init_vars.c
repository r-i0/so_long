#include "../include/so_long.h"

void cnt_map_width(t_vars *vars)
{
	int x;
	int y;
	int width;

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
	vars->map_width = width;
}

void init_vars(t_vars *vars)
{
	int img_width;
	int img_height;

	cnt_map_width(vars);
	vars->mlx = mlx_init();
	vars->mlx_win = mlx_new_window(vars->mlx, vars->map_width * TILE_SIZE, vars->map_height * TILE_SIZE, "so_long");
	vars->img.tile_img = mlx_xpm_file_to_image(vars->mlx, TILE_IMG_PATH, &img_width, &img_height);
	vars->img.player_img = mlx_xpm_file_to_image(vars->mlx, PLAYER_IMG_PATH, &img_width, &img_height);
	vars->img.collectible_img = mlx_xpm_file_to_image(vars->mlx, COLLECTIBLE_IMG_PATH, &img_width, &img_height);
	vars->img.wall_img = mlx_xpm_file_to_image(vars->mlx, WALL_IMG_PATH, &img_width, &img_height);
	vars->img.exit_img = mlx_xpm_file_to_image(vars->mlx, EXIT_IMG_PATH, &img_width, &img_height);
	if (!vars->mlx || !vars->mlx_win || !vars->img.tile_img
		|| !vars->img.player_img || !vars->img.collectible_img
		|| !vars->img.wall_img || !vars->img.exit_img)
		destroy_and_exit(vars);
	vars->collectible = 0;
	vars->collected = 0;
	vars->step_cnt = 0;
}

