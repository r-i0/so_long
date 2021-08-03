#include "../include/so_long.h"

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
			vars->exit_status = EXIT_FAILURE;
			destroy_and_exit(vars);
		}
		y++;
	}
	return (width);
}

void	init_vars(t_vars *vars)
{
	int	x;
	int	y;

	vars->err = false;
	vars->map_width = cnt_map_width(vars);
	vars->mlx = mlx_init();
	vars->mlx_win = mlx_new_window(vars->mlx, vars->map_width * TILE_SIZE,
			vars->map_height * TILE_SIZE, "so_long");
	vars->img.tile_img = mlx_xpm_file_to_image(vars->mlx, TILE_IMG, &x, &y);
	vars->img.player_img = mlx_xpm_file_to_image(vars->mlx, PLAYER_IMG, &x, &y);
	vars->img.collectible_img = mlx_xpm_file_to_image(vars->mlx,
			COLLECTIBLE_IMG, &x, &y);
	vars->img.wall_img = mlx_xpm_file_to_image(vars->mlx, WALL_IMG, &x, &y);
	vars->img.exit_img = mlx_xpm_file_to_image(vars->mlx, EXIT_IMG, &x, &y);
	if (!vars->mlx || !vars->mlx_win || !vars->img.tile_img
		|| !vars->img.player_img || !vars->img.collectible_img
		|| !vars->img.wall_img || !vars->img.exit_img)
		vars->exit_status = EXIT_FAILURE, destroy_and_exit(vars);
	vars->collectible = 0;
	vars->collected = 0;
	vars->step_cnt = 0;
	vars->exit_status = EXIT_SUCCESS;
}
