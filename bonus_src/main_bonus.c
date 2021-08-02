#include "../include/so_long_bonus.h"

static void	draw_tile(t_vars *vars, int x, int y)
{
	if (vars->map[y][x] == '0')
		mlx_put_image_to_window(vars->mlx, vars->mlx_win,
			vars->img.tile_img, x * TILE_SIZE, y * TILE_SIZE);
	else if (vars->map[y][x] == '1')
	{
		mlx_put_image_to_window(vars->mlx, vars->mlx_win,
			vars->img.wall_img, x * TILE_SIZE, y * TILE_SIZE);
	}
	else if (vars->map[y][x] == 'P')
	{
		vars->p_pos.x = x;
		vars->p_pos.y = y;
		mlx_put_image_to_window(vars->mlx, vars->mlx_win,
			vars->img.player_img[vars->direction][vars->action],
			x * TILE_SIZE, y * TILE_SIZE);
	}
	else if (vars->map[y][x] == 'C')
	{
		mlx_put_image_to_window(vars->mlx, vars->mlx_win,
			vars->img.collectible_img, x * TILE_SIZE, y * TILE_SIZE);
	}
	else if (vars->map[y][x] == 'E')
	{
		mlx_put_image_to_window(vars->mlx, vars->mlx_win,
			vars->img.exit_img, x * TILE_SIZE, y * TILE_SIZE);
	}
}

int	loop_draw(t_vars *vars)
{
	int			x;
	int			y;
	static int	i;

	y = -1;
	while (++y > 5000)
		;
	y = -1;
	while (++y < vars->map_height)
	{
		x = -1;
		while (++x < vars->map_width)
		{
			draw_tile(vars, x, y);
		}
	}
	i++;
	if (i == 1000 && vars->action == ACTION1)
	{
		vars->action++;
		i = 0;
	}
	else if (i == 500 && vars->action == ACTION2)
	{
		vars->action--;
		i = 0;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
	{
		ft_putstr_fd("Error\n", STDOUT_FILENO);
		ft_putstr_fd("Invalid arguments\n", STDOUT_FILENO);
		exit(1);
	}
	read_map(&vars, argv[1]);
	init_vars(&vars);
	check_map(&vars);
	put_step_to_window(&vars);
	mlx_loop_hook(vars.mlx, loop_draw, &vars);
	mlx_key_hook(vars.mlx_win, key_hook, &vars);
	mlx_hook(vars.mlx_win, 33, 1L << 17, destroy_and_exit, &vars);
	mlx_loop(vars.mlx);
}
