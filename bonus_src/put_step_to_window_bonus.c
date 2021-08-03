#include "../include/so_long_bonus.h"

char	*strjoin_and_free(char *str1, char *str2, t_vars *vars)
{
	char	*ret;

	ret = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	if (ret == NULL)
		vars->exit_status = EXIT_FAILURE, destroy_and_exit(vars);
	return (ret);
}

void	put_collectible(t_vars *vars)
{
	char	*str1;
	char	*str2;
	char	*num;

	str1 = ft_strdup(" collectible: ");
	if (str1 == NULL)
		vars->exit_status = EXIT_FAILURE, destroy_and_exit(vars);
	num = ft_itoa(vars->collected);
	if (num == NULL)
		vars->exit_status = EXIT_FAILURE, destroy_and_exit(vars);
	str2 = strjoin_and_free(str1, num, vars);
	str1 = ft_strjoin(str2, "/");
	free(str2);
	if (str1 == NULL)
		vars->exit_status = EXIT_FAILURE, destroy_and_exit(vars);
	num = ft_itoa(vars->collectible);
	if (num == NULL)
		vars->exit_status = EXIT_FAILURE, destroy_and_exit(vars);
	str2 = strjoin_and_free(str1, num, vars);
	mlx_string_put(vars->mlx, vars->mlx_win, 100,
		vars->map_height * 40 + 15, 0x00f0f8ff, str2);
	free(str2);
}

void	put_step_count(t_vars *vars)
{
	char	*str1;
	char	*str2;
	char	*step_cnt;

	str1 = ft_strdup(" step count: ");
	if (str1 == NULL)
		vars->exit_status = EXIT_FAILURE, destroy_and_exit(vars);
	step_cnt = ft_itoa(vars->step_cnt);
	if (step_cnt == NULL)
		destroy_and_exit(vars);
	str2 = ft_strjoin(str1, step_cnt);
	free(str1);
	free(step_cnt);
	if (str2 == NULL)
		vars->exit_status = EXIT_FAILURE, destroy_and_exit(vars);
	mlx_string_put(vars->mlx, vars->mlx_win, 0,
		vars->map_height * 40 + 15, 0x00f0f8ff, str2);
	free(str2);
}

void	put_info_to_window(t_vars *vars)
{
	put_back_gray(vars);
	put_step_count(vars);
	put_collectible(vars);
	vars->step_cnt++;
}
