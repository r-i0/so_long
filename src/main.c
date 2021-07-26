#include "../include/so_long.h"

void	clear_screen(void)
{
	ft_putstr_fd("\033[2J", STDOUT_FILENO);
	ft_putstr_fd("\033[", STDOUT_FILENO);
	ft_putnbr_fd(1, STDOUT_FILENO);
	ft_putstr_fd(";", STDOUT_FILENO);
	ft_putnbr_fd(1, STDOUT_FILENO);
	ft_putstr_fd("H", STDOUT_FILENO);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	clear_screen();
	if (argc != 2)
	{
		ft_putstr_fd("Error\n", STDOUT_FILENO);
		ft_putstr_fd("Invalid arguments\n", STDOUT_FILENO);
		exit(1);
	}
	read_map(&vars, argv[1]);
	init_vars(&vars);
	check_map(&vars);
	mlx_loop_hook(vars.mlx, loop_draw, &vars);
	mlx_key_hook(vars.mlx_win, key_hook, &vars);
	mlx_hook(vars.mlx_win, 33, 1L << 17, destroy_and_exit, &vars);
	mlx_loop(vars.mlx);
}
