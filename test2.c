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
		exit(0);
	}
	return 0;
}

int	min(int n1, int n2)
{
	if (n1 > n2)
		return (n2);
	return (n1);
}

int	max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}

void	swap(int *i, int *j)
{
	int	t;
	
	t = *i;
	*i = *j;
	*j = t;
}

int	absv(int i)
{
	if (i < 0)
		i *= -1;
	return (i);
}

typedef struct s_line
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
}	t_line;

typedef struct s_delta
{
	int	dx;
	int	dy;
	int	d;
	int	xs;
	int	ys;
}	t_delta;

void slop(t_line line, t_delta *delta)
{
	delta->dx = line.x2 - line.x1;
	delta->dy = line.y2 - line.y1;
	if (delta->dx >= 0)
		delta->xs = 1;
	else
		delta->xs = -1;
	if (delta->dy >= 0)
		delta->ys = 1;
	else
		delta->ys = -1;
	delta->dx = absv(delta->dx);
	delta->dy = absv(delta->dy);
}
// line.x1 = 29;
// 	line.y1 = 101;
// 	line.x2 = 36;
// 	line.y2 = 105;
// dx = 7 | dx = 4
void	drow_line(t_line line, t_data *img)
{
	t_delta	delta;

	slop(line, &delta);
	if (delta.dx > delta.dy)
	{
		printf("%i %i\n", delta.dx, delta.dy);
		delta.d = 2 * delta.dy - delta.dx;
		for (int i = 0; i < delta.dx; i++)
		{
			my_mlx_pixel_put(img, line.x1, line.y1, 0x00CCCC00);
			line.x1 += delta.xs;
			if (delta.d < 0)
				delta.d += (2 * delta.dy);
			else
			{
				delta.d += 2 * (delta.dy - delta.dx);
				line.y1 += delta.ys;
			}
		}
	}
	else
	{
		printf("dd\n");

		delta.d = 2 * delta.dx - delta.dy;
		for (int i = 0; i < delta.dy; i++)
		{
			my_mlx_pixel_put(img, line.x1, line.y1, 0x00CCCC00);
			line.y1 += delta.ys;
			if (delta.d < 0)
				delta.d += (2 * delta.dx);
			else
			{
				delta.d += 2 * (delta.dx - delta.dy);
				line.x1 += delta.xs;
			}
		}
	}
}

void plotLine(int x0, int y0, int x1, int y1, t_data *data)
{
   int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
   int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1; 
   int err = dx+dy, e2; /* error value e_xy */
 
   for(;;){  /* loop */
      my_mlx_pixel_put(data, x0, y0, 0x00CCCC00);
      if (x0==x1 && y0==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
   }
}

int	main(void)
{
	t_data	img;
	t_data	img2;
	t_vars	vars;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (1);
	vars.win = mlx_new_window(vars.mlx, 1000, 1000, "Hello world!");
	if (!vars.win)
		exit(1);
	img.img = mlx_new_image(vars.mlx, 500, 500);
	if (!img.img)
	{
		mlx_destroy_window(vars.mlx, vars.win);
		exit(1);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	vars.img = &img;
	img2.img = mlx_new_image(vars.mlx, 500, 500);
	img2.addr = mlx_get_data_addr(img2.img, &img2.bits_per_pixel, &img2.line_length, &img2.endian);
	mlx_hook(vars.win, 2, (1L<<3), close22, &vars);

	// plotLine(300, 300, 300, 50, &img);
	t_line line;
	line.x1 = 29;
	line.y1 = 101;
	line.x2 = 36;
	line.y2 = 105;
	plotLine(29, 101, 36, 105, &img);
	drow_line(line, &img2);
	mlx_put_image_to_window(vars.mlx , vars.win, img.img, 0, 0);
	mlx_put_image_to_window(vars.mlx , vars.win, img2.img, 500, 500);

	
	mlx_loop(vars.mlx);

	mlx_destroy_image(vars.mlx, vars.win);
	mlx_destroy_window(vars.mlx, vars.win);
	exit(1);
}