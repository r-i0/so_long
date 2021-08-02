#include "../include/so_long_bonus.h"

int	check_end(t_vars *vars)
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
	}
	return (0);
}

int	move_player(t_vars *vars, int next_x, int next_y)
{
	if (vars->map[vars->p_pos.y + next_y][vars->p_pos.x + next_x] == '1')
		return (0);
	if (vars->map[vars->p_pos.y + next_y][vars->p_pos.x + next_x] == 'C')
	{
		vars->collected++;
		vars->map[vars->p_pos.y + next_y][vars->p_pos.x + next_x] = '0';
	}
	if (vars->map[vars->p_pos.y + next_y][vars->p_pos.x + next_x] == 'E')
	{
		return (check_end(vars));
	}
	vars->map[vars->p_pos.y + next_y][vars->p_pos.x + next_x] = 'P';
	vars->map[vars->p_pos.y][vars->p_pos.x] = '0';
	vars->p_pos.x += next_x;
	vars->p_pos.y += next_y;
	return (1);
}

void	put_step_count(t_vars *vars)
{
	char	*str;

	str = ft_strdup("step count: ");
	if (str == NULL)
		destroy_and_exit(vars);
	str = ft_strjoin(str, ft_itoa(vars->step_cnt));
	mlx_string_put(vars->mlx, vars->mlx_win, 0, vars->map_height * 40 + 15, 0x00f0f8ff, str);
}

void	put_back_gray(t_vars *vars)
{
	int	x;

	x = 0;
	while (x < vars->map_width)
	{
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.gray_img, x * TILE_SIZE, vars->map_height * TILE_SIZE);
		x++;
	}
}

void	put_collectible(t_vars *vars)
{
	char	*str;

	str = ft_strdup("collectible: ");
	if (str == NULL)
		destroy_and_exit(vars);
	str = ft_strjoin(str, ft_itoa(vars->collected));
	str = ft_strjoin(str, "/");
	str = ft_strjoin(str, ft_itoa(vars->collectible));
	mlx_string_put(vars->mlx, vars->mlx_win, 120, vars->map_height * 40 + 15, 0x00f0f8ff, str);
}

void	put_step_to_window(t_vars *vars)
{
	put_back_gray(vars);
	put_step_count(vars);
	put_collectible(vars);
}

int	key_hook(int key_code, t_vars *vars)
{
	int	move;

	move = 0;
	if (key_code == W)
	{
		vars->direction = BACK;
		move = move_player(vars, 0, -1);
	}
	if (key_code == A)
	{
		vars->direction = LEFT;
		move = move_player(vars, -1, 0);
	}
	if (key_code == S)
	{
		vars->direction = FRONT;
		move = move_player(vars, 0, 1);
	}
	if (key_code == D)
	{
		vars->direction = RIGHT;
		move = move_player(vars, 1, 0);
	}
	if (key_code == ESC)
		destroy_and_exit(vars);
	if (move)
	{
		put_step_to_window(vars);
		printf("\033[2J\033[%d;%dH", 1, 1);
		printf("step count: %d\n", vars->step_cnt);
		printf("collectible: %d/%d\n", vars->collected, vars->collectible);
		vars->step_cnt++;
	}
	return (0);
}
