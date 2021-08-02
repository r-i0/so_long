#include "../include/so_long_bonus.h"

void	put_end_message(t_vars *vars)
{
	char	*str1;
	char	*str2;
	char	*step_cnt;

	str1 = ft_strdup(" STAGE CLEAR!!  Your steps were ");
	if (str1 == NULL)
		destroy_and_exit(vars);
	step_cnt = ft_itoa(vars->step_cnt);
	if (step_cnt == NULL)
		destroy_and_exit(vars);
	str2 = ft_strjoin(str1, step_cnt);
	free(str1);
	free(step_cnt);
	if (str2 == NULL)
		destroy_and_exit(vars);
	put_back_gray(vars);
	mlx_string_put(vars->mlx, vars->mlx_win, 0,
		vars->map_height * 40 + 15, 0x00f0f8ff, str2);
	free(str2);
}

int	check_end(t_vars *vars, int next_x, int next_y)
{
	if (vars->collectible == vars->collected)
	{
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.p_exit,
			(vars->p_pos.x + next_x) * TILE_SIZE,
			(vars->p_pos.y + next_y) * TILE_SIZE);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img.tile_img,
			vars->p_pos.x * TILE_SIZE, vars->p_pos.y * TILE_SIZE);
		put_end_message(vars);
		vars->end = true;
	}
	else
	{
		mlx_string_put(vars->mlx, vars->mlx_win, 220,
			vars->map_height * 40 + 15, 0x00f0f8ff,
			"You don't have enough collectible");
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
		return (check_end(vars, next_x, next_y));
	}
	vars->map[vars->p_pos.y + next_y][vars->p_pos.x + next_x] = 'P';
	vars->map[vars->p_pos.y][vars->p_pos.x] = '0';
	vars->p_pos.x += next_x;
	vars->p_pos.y += next_y;
	return (1);
}

int	move_player_direction(t_vars *vars, int key_code)
{
	if (key_code == W)
	{
		vars->direction = BACK;
		return (move_player(vars, 0, -1));
	}
	if (key_code == A)
	{
		vars->direction = LEFT;
		return (move_player(vars, -1, 0));
	}
	if (key_code == S)
	{
		vars->direction = FRONT;
		return (move_player(vars, 0, 1));
	}
	if (key_code == D)
	{
		vars->direction = RIGHT;
		return (move_player(vars, 1, 0));
	}
	return (0);
}

int	key_hook(int key_code, t_vars *vars)
{
	int	move;

	move = move_player_direction(vars, key_code);
	if (key_code == ESC)
		destroy_and_exit(vars);
	if (move)
		put_info_to_window(vars);
	return (0);
}
