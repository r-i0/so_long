#include "./include/so_long.h"

void	destroy_and_exit(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->player_img);
	mlx_destroy_image(vars->mlx, vars->tile_img);
	mlx_destroy_image(vars->mlx, vars->wall_img);
	mlx_destroy_image(vars->mlx, vars->exit_img);
	mlx_destroy_image(vars->mlx, vars->collectible_img);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(EXIT_SUCCESS);
}

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
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->player_img, vars->player_point.x * TILE_SIZE, vars->player_point.y * TILE_SIZE);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->tile_img, (vars->player_point.x - next_pos_x) * TILE_SIZE, (vars->player_point.y - next_pos_y) * TILE_SIZE);
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
	if (tmp[0])
		i++;
	free(tmp);
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
	if (tmp[0])
	{
		vars->map[i] = tmp;
		i++;
	}
}

void	cnt_map_width(t_vars *vars)
{
	int	x;
	int	y;
	int	width;

	y = 0;
	width = 0;
	while (vars->map[y])
	{
		x = 0;
		while (vars->map[y][x])
			x++;
		if (width == 0)
			width = x;
		else if (width != x)
		{
			printf("error\n");
		}
		y++;
	}
	vars->map_width = width;
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
			if (vars->map[y][x] == '0')
				mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->tile_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (vars->map[y][x] == '1')
				mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->wall_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (vars->map[y][x] == 'P')
			{
				vars->player_point.x = x;
				vars->player_point.y = y;
				cnt_chr.cnt_player++;
				mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->player_img, x * TILE_SIZE, y * TILE_SIZE);
			}
			else if (vars->map[y][x] == 'C')
			{
				vars->collectible++;
				mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->collectible_img, x * TILE_SIZE, y * TILE_SIZE);
			}
			else if (vars->map[y][x] == 'E')
			{
				cnt_chr.cnt_exit++;
				mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->exit_img, x * TILE_SIZE, y * TILE_SIZE);
			}
			else
			{
				printf("invalid map\n");

			}
		}
	}
	if (cnt_chr.cnt_player != 1 || !cnt_chr.cnt_exit || !vars->collectible)
	{
		printf("invalid map\n");
		destroy_and_exit(vars);
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
	vars->exit_img = mlx_xpm_file_to_image(vars->mlx, EXIT_IMG_PATH, &img_width, &img_height);
	vars->collectible = 0;
	vars->collected = 0;
	vars->step_cnt = 0;
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	printf("\033[2J\033[%d;%dH", 1, 1);
	read_map(&vars, argv[1]);
	vars_init(&vars);
	gen_map(&vars);
	mlx_key_hook(vars.mlx_win, key_hook, &vars);
	mlx_loop(vars.mlx);
}