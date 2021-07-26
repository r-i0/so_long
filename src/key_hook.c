#include "../include/so_long.h"

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
