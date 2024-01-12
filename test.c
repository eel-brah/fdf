#include <mlx.h>
#include <libc.h>

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

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_data	*img;
}				t_vars;

int	close22(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_image(vars->mlx, vars->img->img);
		mlx_destroy_window(vars->mlx, vars->win);
		//mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(0);
	}
	return 0;
}

typedef struct s_sqiare
{
	t_vars *vars;
	int i;
}	t_square;

int square(t_square *sq)
{
	if (sq->i == 1)
	{
		for (int i = 99; i < 400; i++)
			my_mlx_pixel_put(sq->vars->img, 99, i, 0x00CCCC00);
		for (int i = 99; i < 400; i++)
			my_mlx_pixel_put(sq->vars->img, i, 99, 0x00CCCC00);
		for (int i = 399; i > 100; i--)
			my_mlx_pixel_put(sq->vars->img, 400, i, 0x00CCCC00);
		for (int i = 399; i > 100; i--)
			my_mlx_pixel_put(sq->vars->img, i, 400, 0x00CCCC00);
		sleep(1);
		mlx_put_image_to_window(sq->vars->mlx , sq->vars->win, sq->vars->img->img, 0, 0);
		sq->i = 2;
	}
	else if (sq->i == 2)
	{
		for (int i = 149; i < 349; i++)
			my_mlx_pixel_put(sq->vars->img, 149, i, 0x00CCCC00);
		for (int i = 149; i < 349; i++)
			my_mlx_pixel_put(sq->vars->img, i, 149, 0x00CCCC00);
		for (int i = 349; i > 150; i--)
			my_mlx_pixel_put(sq->vars->img, 349, i, 0x00CCCC00);
		for (int i = 349; i > 150; i--)
			my_mlx_pixel_put(sq->vars->img, i, 349, 0x00CCCC00);
		sleep(1);
		mlx_put_image_to_window(sq->vars->mlx , sq->vars->win, sq->vars->img->img, 0, 0);
		sq->i = 3;
	}
	else if (sq->i == 3)
	{
		for (int i = 199; i < 300; i++)
			my_mlx_pixel_put(sq->vars->img, 199, i, 0x00CCCC00);
		for (int i = 199; i < 300; i++)
			my_mlx_pixel_put(sq->vars->img, i, 199, 0x00CCCC00);
		for (int i = 299; i > 200; i--)
			my_mlx_pixel_put(sq->vars->img, 300, i, 0x00CCCC00);
		for (int i = 299; i > 200; i--)
			my_mlx_pixel_put(sq->vars->img, i, 300, 0x00CCCC00);
		sleep(1);
		mlx_put_image_to_window(sq->vars->mlx , sq->vars->win, sq->vars->img->img, 0, 0);
		sq->i = 4;
	}
	else if (sq->i == 4)
	{
		for (int i = 99; i < 400; i++)
			my_mlx_pixel_put(sq->vars->img, i, i, 0x00CCCC00);
		for (int i = 400, j = 100; i > 100; i--, j++)
		{
			my_mlx_pixel_put(sq->vars->img, i, j, 0x00CCCC00);
		}
		sleep(1);
		mlx_put_image_to_window(sq->vars->mlx , sq->vars->win, sq->vars->img->img, 0, 0);
		sq->i = 0;
	}
	return 0;
}

int	main(void)
{
	t_data	img;
	t_vars	vars;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (1);
	vars.win = mlx_new_window(vars.mlx, 500, 500, "Hello world!");
	if (!vars.win)
	{
		//mlx_destroy_display(vars.mlx);
		free(vars.mlx);
		return (1);
	}
	img.img = mlx_new_image(vars.mlx, 500, 500);
	if (!img.img)
	{
		mlx_destroy_window(vars.mlx, vars.win);
		//mlx_destroy_display(vars.mlx);
		free(vars.mlx);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	vars.img = &img;
	t_square sq;
	sq.i = 1;
	sq.vars = &vars;
	mlx_loop_hook(vars.mlx, square, &sq);
	mlx_hook(vars.win, 2, (1L<<3), close22, &vars);
	mlx_loop(vars.mlx);

	mlx_destroy_image(vars.mlx, vars.win);
	mlx_destroy_window(vars.mlx, vars.win);
	//mlx_destroy_display(vars.mlx);
	free(vars.mlx);
}