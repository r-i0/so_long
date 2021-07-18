#include "./include/so_long.h"
#include <stdio.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	// void	*img;
	// int		img_width;
	// int		img_height;
	// char	*relative_path = "./test.xpm";

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");

	img.img = mlx_new_image(mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	int x = -1;
	int y;
	int dx;
	int dy;
	while (++x < 500)
	{
		y = -1;
		while (++y < 500)
		{
			dx = x - 250;
			dy = y - 250;
			if ((dx * dx) + (dy * dy) <= (100 * 100))
			{
				my_mlx_pixel_put(&img, x, y, 0x00FFFF00);
			}
		}
	}
	// img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
