#include "../include/so_long_bonus.h"

void	destroy_player_img(t_vars *vars)
{
	if (vars->img.player_img[FRONT][ACTION1])
		mlx_destroy_image(vars->mlx, vars->img.player_img[FRONT][ACTION1]);
	if (vars->img.player_img[FRONT][ACTION2])
		mlx_destroy_image(vars->mlx, vars->img.player_img[FRONT][ACTION2]);
	if (vars->img.player_img[LEFT][ACTION1])
		mlx_destroy_image(vars->mlx, vars->img.player_img[LEFT][ACTION1]);
	if (vars->img.player_img[LEFT][ACTION2])
		mlx_destroy_image(vars->mlx, vars->img.player_img[LEFT][ACTION2]);
	if (vars->img.player_img[RIGHT][ACTION1])
		mlx_destroy_image(vars->mlx, vars->img.player_img[RIGHT][ACTION1]);
	if (vars->img.player_img[RIGHT][ACTION2])
		mlx_destroy_image(vars->mlx, vars->img.player_img[RIGHT][ACTION2]);
	if (vars->img.player_img[BACK][ACTION1])
		mlx_destroy_image(vars->mlx, vars->img.player_img[BACK][ACTION1]);
	if (vars->img.player_img[BACK][ACTION2])
		mlx_destroy_image(vars->mlx, vars->img.player_img[BACK][ACTION2]);
}

void	img_destroy(t_vars *vars)
{
	destroy_player_img(vars);
	if (vars->img.tile_img)
		mlx_destroy_image(vars->mlx, vars->img.tile_img);
	if (vars->img.wall_img)
		mlx_destroy_image(vars->mlx, vars->img.wall_img);
	if (vars->img.exit_img)
		mlx_destroy_image(vars->mlx, vars->img.exit_img);
	if (vars->img.collectible_img)
		mlx_destroy_image(vars->mlx, vars->img.collectible_img);
	if (vars->img.gray_img)
		mlx_destroy_image(vars->mlx, vars->img.gray_img);
	if (vars->img.p_exit)
		mlx_destroy_image(vars->mlx, vars->img.p_exit);
}

int	destroy_and_exit(t_vars *vars)
{
	int	i;

	i = -1;
	if (vars->mlx_win)
		mlx_destroy_window(vars->mlx, vars->mlx_win);
	img_destroy(vars);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	if (vars->map)
	{
		while (vars->map[++i])
			free(vars->map[i]);
		free(vars->map);
	}
	exit(EXIT_SUCCESS);
	return (0);
}
