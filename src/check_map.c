#include "../include/so_long.h"

void	is_valid_chr(t_vars *vars, int x, int y, t_cntchr *cnt_chr)
{
	if (vars->map[y][x] == 'P')
	{
		vars->p_pos.x = x;
		vars->p_pos.y = y;
		cnt_chr->cnt_player++;
	}
	else if (vars->map[y][x] == 'C')
	{
		vars->collectible++;
	}
	else if (vars->map[y][x] == 'E')
	{
		cnt_chr->cnt_exit++;
	}
	else if (vars->map[y][x] != '0' && vars->map[y][x] != '1')
	{
		vars->err = true;
	}
}

bool	check_closed(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->map[i])
	{
		if (vars->map[i][0] != '1' || vars->map[i][vars->map_width - 1] != '1')
		{
			return (true);
		}
		i++;
	}
	i = 0;
	while (vars->map[0][i])
	{
		if (vars->map[0][i] != '1' || vars->map[vars->map_height - 1][i] != '1')
		{
			return (true);
		}
		i++;
	}
	return (false);
}

int	check_map(t_vars *vars)
{
	t_cntchr	cnt_chr;
	int			x;
	int			y;

	cnt_chr.cnt_player = 0;
	cnt_chr.cnt_exit = 0;
	y = -1;
	while (++y < vars->map_height)
	{
		x = -1;
		while (++x < vars->map_width)
		{
			is_valid_chr(vars, x, y, &cnt_chr);
		}
	}
	if (cnt_chr.cnt_player != 1 || !cnt_chr.cnt_exit
		|| !vars->collectible || vars->err || check_closed(vars))
	{
		ft_putstr_fd("Error\n", STDOUT_FILENO);
		ft_putstr_fd("Invalid map\n", STDOUT_FILENO);
		destroy_and_exit(vars);
	}
	return (0);
}
