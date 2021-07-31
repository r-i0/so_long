#include "../include/so_long_bonus.h"

static void	img_init(t_vars *vars)
{
	vars->map = NULL;
	vars->mlx = NULL;
	vars->mlx_win = NULL;
	vars->img.player_img[0] = NULL;//
	vars->img.tile_img = NULL;
	vars->img.wall_img = NULL;
	vars->img.exit_img = NULL;
	vars->img.collectible_img = NULL;
}

static int	check_tmp(t_vars *vars, int ret, char *tmp, int flag)
{
	if (ret == -1)
		exit(1);
	if (tmp[0])
	{
		if (vars->map_height && flag == 0)
		{
			vars->err = true;
		}
		vars->map_height++;
		return (1);
	}
	else
		return (0);
}

static void	cnt_map_height(t_vars *vars, char *map_name)
{
	int		fd;
	int		ret;
	char	*tmp;
	int		flag;

	flag = 0;
	vars->map_height = 0;
	img_init(vars);
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\n", STDOUT_FILENO);
		perror(map_name);
		destroy_and_exit(vars);
	}
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &tmp);
		flag = check_tmp(vars, ret, tmp, flag);
		free(tmp);
	}
	close(fd);
}

void	read_map(t_vars *vars, char *map_name)
{
	int		fd;
	char	*tmp;
	int		i;
	int		ret;

	cnt_map_height(vars, map_name);
	fd = open(map_name, O_RDONLY);
	vars->map = (char **)malloc(sizeof(char *) * (vars->map_height + 1));
	if (!vars->map)
		exit(EXIT_FAILURE);
	i = 0;
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &tmp);
		if (ret == -1)
		{
			destroy_and_exit(vars);
		}
		if (tmp[0])
			vars->map[i++] = tmp;
		else
			free(tmp);
	}
	vars->map[i] = NULL;
}
