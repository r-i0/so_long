#include "./include/so_long.h"

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

void	read_map(t_vars *vars, char *map_name)
{
	int	fd;
	char *tmp;
	int i;

	i = 0;
	fd = open(map_name, O_RDONLY);
	while (get_next_line(fd, &tmp))
	{
		if (tmp[0])
			i++;
		free(tmp);
	}
	vars->map_height = i;
	close(fd);
	fd = open(map_name, O_RDONLY);
	vars->map = (char**)malloc(sizeof(char*) * vars->map_height);
	i = 0;
	while (get_next_line(fd, &tmp))
	{
		if (tmp[0])
		{
			vars->map[i] = tmp;
			i++;
		}
	}
}

void	cnt_map_width(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->map[0][i])
	{
		i++;
	}
	vars->map_width = i;
}

void	gen_map(t_vars *vars)
{
	int		img_width;
	int		img_height;

	cnt_map_width(vars);
	vars->player_point.x = 0;
	vars->player_point.y = 0;

	printf("height: %d\n", vars->map_height);
	printf("width: %d\n", vars->map_width);
	vars->mlx_win = mlx_new_window(vars->mlx, vars->map_width * 60, vars->map_height * 60, "so_long");
	vars->tile_img = mlx_xpm_file_to_image(vars->mlx, tile_img_path, &img_width, &img_height);
	vars->player_img = mlx_xpm_file_to_image(vars->mlx, player_img_path, &img_width, &img_height);
	vars->collectible_img = mlx_xpm_file_to_image(vars->mlx, collectible_img_path, &img_width, &img_height);
	int x = 0;
	int y;
	while (x < 600)
	{
		y = 0;
		while (y < 600)
		{
			mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->tile_img, x, y);
			y += 60;
		}
		x += 60;
	}
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->player_img, vars->player_point.x, vars->player_point.y);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->collectible_img, 120, 120);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		img_width;
	int		img_height;

	vars.mlx = mlx_init();
	read_map(&vars, argv[1]);
	gen_map(&vars);

	mlx_key_hook(vars.mlx_win, key_hook, &vars);
	mlx_loop(vars.mlx);
}