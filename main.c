#include "./include/so_long.h"

int	key_hook(int key_code, t_vars *vars)
{
	static int cnt;
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
	printf("cnt : %d\n", cnt);
	cnt++;
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
	int		x;
	int		y;

	y = 0;

	vars->player_point.x = 60;
	vars->player_point.y = 60;

	while (y < vars->map_height)
	{
		x = 0;
		while (x < vars->map_width)
		{
			if (vars->map[y][x] == '0')
				mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->tile_img, x * TILE_SIZE, y * TILE_SIZE);
			if (vars->map[y][x] == '1')
				mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->wall_img, x * TILE_SIZE, y * TILE_SIZE);
			if (vars->map[y][x] == 'P')
				mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->player_img, x * TILE_SIZE, y * TILE_SIZE);
			if (vars->map[y][x] == 'C')
				mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->collectible_img, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	vars_init(t_vars *vars)
{
	int		img_width;
	int		img_height;

	cnt_map_width(vars);
	vars->mlx = mlx_init();
	vars->mlx_win = mlx_new_window(vars->mlx, vars->map_width * TILE_SIZE, vars->map_height * TILE_SIZE, "so_long");
	vars->tile_img = mlx_xpm_file_to_image(vars->mlx, TILE_IMG_PATH, &img_width, &img_height);
	vars->player_img = mlx_xpm_file_to_image(vars->mlx, PLAYER_IMG_PATH, &img_width, &img_height);
	vars->collectible_img = mlx_xpm_file_to_image(vars->mlx, COLLECTIBLE_IMG_PATH, &img_width, &img_height);
	vars->wall_img = mlx_xpm_file_to_image(vars->mlx, WALL_IMG_PATH, &img_width, &img_height);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		img_width;
	int		img_height;

	read_map(&vars, argv[1]);
	vars_init(&vars);
	gen_map(&vars);

	mlx_key_hook(vars.mlx_win, key_hook, &vars);
	mlx_loop(vars.mlx);
}