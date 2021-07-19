#include "./include/so_long.h"
#include <stdlib.h>

int	key_hook(int key_code, t_vars *vars)
{
	if (key_code == W)
	{
		vars->player_point.y -= 60;
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->player_img, vars->player_point.x, vars->player_point.y);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->tile_img, vars->player_point.x, vars->player_point.y + 60);
	}
	if (key_code == A)
	{
		vars->player_point.x -= 60;
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->player_img, vars->player_point.x, vars->player_point.y);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->tile_img, vars->player_point.x + 60, vars->player_point.y);
	}
	if (key_code == S)
	{
		vars->player_point.y += 60;
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->player_img, vars->player_point.x, vars->player_point.y);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->tile_img, vars->player_point.x, vars->player_point.y - 60);
	}
	if (key_code == D)
	{
		vars->player_point.x +=60;
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->player_img, vars->player_point.x, vars->player_point.y);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->tile_img, vars->player_point.x - 60, vars->player_point.y);
	}
	printf("key_code : %d\n", key_code);
	return (0);
}

int	main(void)
{
	t_vars	vars;
	char	*player_img_path = "./player3.xpm";
	char	*relative_path = "./WorldMap-A2.xpm";
	int		img_width;
	int		img_height;

	vars.player_point.x = 300;
	vars.player_point.y = 300;

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 600, 600, "so_long");
	vars.tile_img = mlx_xpm_file_to_image(vars.mlx, relative_path, &img_width, &img_height);
	vars.player_img = mlx_xpm_file_to_image(vars.mlx, player_img_path, &img_width, &img_height);
	int x = 0;
	int y = 0;
	// mlx_put_image_to_window(mlx, mlx_win, img, x, y);
	while (x < 600)
	{
		y = 0;
		while (y < 600)
		{
			mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.tile_img, x, y);
			y += 60;
		}
		x += 60;
	}
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.player_img, vars.player_point.x, vars.player_point.y);

	mlx_key_hook(vars.mlx_win, key_hook, &vars);
	mlx_loop(vars.mlx);
}