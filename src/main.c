#include "../include/so_long.h"



int	move_player(t_vars *vars, int next_pos_x, int next_pos_y)
{
	if (vars->map[vars->player_point.y + next_pos_y][vars->player_point.x + next_pos_x] == '1')
		return (0);
	if (vars->map[vars->player_point.y + next_pos_y][vars->player_point.x + next_pos_x] == 'C')
	{
		vars->collected++;
		vars->map[vars->player_point.y + next_pos_y][vars->player_point.x + next_pos_x] = '0';
	}
	if (vars->map[vars->player_point.y + next_pos_y][vars->player_point.x + next_pos_x] == 'E')
	{
		if (vars->collectible == vars->collected)
		{
			printf("\033[2J\033[%d;%dH", 2, 1);
			printf("Your steps were \033[4m%d\033[0m\n\n", vars->step_cnt);
			destroy_and_exit(vars);
		}
		else
		{
			printf("\033[%d;%dH", 3, 1);
			printf("You don't have enough collectible\n");
			return (0);
		}
	}
	vars->player_point.x += next_pos_x;
	vars->player_point.y += next_pos_y;
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.player_img, vars->player_point.x * TILE_SIZE, vars->player_point.y * TILE_SIZE);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.tile_img, (vars->player_point.x - next_pos_x) * TILE_SIZE, (vars->player_point.y - next_pos_y) * TILE_SIZE);
	return (1);
}

int	key_hook(int key_code, t_vars *vars)
{
	int	move;

	if (key_code == W)
		move = move_player(vars, 0, -1);
	if (key_code == A)
		move = move_player(vars, -1, 0);
	if (key_code == S)
		move = move_player(vars, 0, 1);
	if (key_code == D)
		move = move_player(vars, 1, 0);
	if (key_code == ESC)
		destroy_and_exit(vars);
	if (move)
	{
		printf("\033[2J\033[%d;%dH", 1, 1);
		printf("step count: %d\n", vars->step_cnt);
		printf("collectible: %d/%d\n", vars->collected, vars->collectible);
		vars->step_cnt++;
	}
	return (0);
}

void	put_map_image(t_vars *vars, int x, int y, t_cntchr *cnt_chr)
{
	if (vars->map[y][x] == '0')
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.tile_img, x * TILE_SIZE, y * TILE_SIZE);
	else if (vars->map[y][x] == '1')
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.wall_img, x * TILE_SIZE, y * TILE_SIZE);
	else if (vars->map[y][x] == 'P')
	{
		vars->player_point.x = x;
		vars->player_point.y = y;
		cnt_chr->cnt_player++;
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.player_img, x * TILE_SIZE, y * TILE_SIZE);
	}
	else if (vars->map[y][x] == 'C')
	{
		vars->collectible++;
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.collectible_img, x * TILE_SIZE, y * TILE_SIZE);
	}
	else if (vars->map[y][x] == 'E')
	{
		cnt_chr->cnt_exit++;
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.exit_img, x * TILE_SIZE, y * TILE_SIZE);
	}
	else
	{
		ft_putstr_fd("Error\n", STDOUT_FILENO);
		ft_putstr_fd("Invalid map\n", STDOUT_FILENO);
		destroy_and_exit(vars);
	}
}

void	gen_map(t_vars *vars)
{
	int		x;
	int		y;
	t_cntchr	cnt_chr;

	cnt_chr.cnt_player = 0;
	cnt_chr.cnt_exit = 0;
	y = -1;
	while (++y < vars->map_height)
	{
		x = -1;
		while (++x < vars->map_width)
		{
			put_map_image(vars, x, y, &cnt_chr);
		}
	}
	if (cnt_chr.cnt_player != 1 || !cnt_chr.cnt_exit || !vars->collectible)
	{
		ft_putstr_fd("Error\n", STDOUT_FILENO);
		ft_putstr_fd("Invalid map\n", STDOUT_FILENO);
		destroy_and_exit(vars);
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	// printf("\033[2J\033[%d;%dH", 1, 1);
	ft_putstr_fd("\033[2J", STDOUT_FILENO);
	ft_putstr_fd("\033[", STDOUT_FILENO);
	ft_putnbr_fd(1, STDOUT_FILENO);
	ft_putstr_fd(";", STDOUT_FILENO);
	ft_putnbr_fd(1, STDOUT_FILENO);
	ft_putstr_fd("H", STDOUT_FILENO);
	// fflush(stdout);
	if (argc != 2)
	{
		ft_putstr_fd("Error\n", STDOUT_FILENO);
		ft_putstr_fd("Invalid argments\n", STDOUT_FILENO);
		exit(1);
	}
	read_map(&vars, argv[1]);
	init_vars(&vars);
	// mlx_get_screen_size(vars.mlx, &sizex, &sizey);
	gen_map(&vars);
	// mlx_do_key_autorepeaton(&vars.mlx);
	mlx_key_hook(vars.mlx_win, key_hook, &vars);
	mlx_hook(vars.mlx_win, 33, 1L << 17, destroy_and_exit, &vars);
	mlx_loop(vars.mlx);
}