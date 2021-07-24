#include "../include/so_long.h"

void	img_init(t_vars *vars)
{
	vars->img.player_img = NULL;
	vars->img.tile_img = NULL;
	vars->img.wall_img = NULL;
	vars->img.exit_img = NULL;
	vars->img.collectible_img = NULL;
}

void	cnt_map_height(t_vars *vars, char *map_name)
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
		exit(1);
	}
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &tmp);
		if (ret == -1)
			exit(1);
		if (tmp[0])
		{
			if (vars->map_height && flag == 0)
			{
				ft_putstr_fd("Error\n", STDOUT_FILENO);
				ft_putstr_fd("Invalid map\n", STDOUT_FILENO);
				destroy_and_exit(vars);
			}
			vars->map_height++;
			flag = 1;
		}
		else
			flag = 0;
		free(tmp);
	}
	close(fd);
}

void read_map(t_vars *vars, char *map_name)
{
	int fd;
	char *tmp;
	int i;
	int ret;

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
			while (vars->map[++i])
				free(vars->map[i]);
			free(vars->map);
			exit(EXIT_FAILURE);
		}
		if (tmp[0])
		{
			vars->map[i] = tmp;
			i++;
		}
		else
			free(tmp);
	}
	vars->map[i] = NULL;
}

// int a = 0;
// int b;
// while (vars->map[a])
// {
// 	b = 0;
// 	while (vars->map[a][b])
// 	{
// 		printf("%c", vars->map[a][b]);
// 		b++;
// 	}
// 	a++;
// 	printf("\n");
// }
// exit(0);