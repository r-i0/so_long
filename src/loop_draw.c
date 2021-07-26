#include "../include/so_long.h"

void	draw_tile(t_vars *vars, int x, int y)
{
	if (vars->map[y][x] == '0')
		mlx_put_image_to_window(vars->mlx, vars->mlx_win,
			vars->img.tile_img, x * TILE_SIZE, y * TILE_SIZE);
	else if (vars->map[y][x] == '1')
		mlx_put_image_to_window(vars->mlx, vars->mlx_win,
			vars->img.wall_img, x * TILE_SIZE, y * TILE_SIZE);
	else if (vars->map[y][x] == 'P')
	{
		vars->p_pos.x = x;
		vars->p_pos.y = y;
		mlx_put_image_to_window(vars->mlx, vars->mlx_win,
			vars->img.player_img, x * TILE_SIZE, y * TILE_SIZE);
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
	int	x;
	int	y;

	y = -1;
	while (++y < vars->map_height)
	{
		x = -1;
		while (++x < vars->map_width)
		{
			draw_tile(vars, x, y);
		}
	}
	while (++x < 10000)
		write(2, "", 0);
	return (0);
}
