/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:30:22 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/15 21:27:57 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_x(t_clear *clear)
{
	free_map(clear->map);
	close(clear->fd);
	mlx_destroy_image(clear->vars->mlx, clear->vars->img->img);
	mlx_destroy_window(clear->vars->mlx, clear->vars->win);
	//mlx_destroy_display(clear->vars.mlx);
	// free(clear->vars->mlx);
}

int close_w(t_clear *clear)
{
	clear_x(clear);
	exit(0);
}

int	key_handler(int keysym, t_clear *clear)
{
	if (keysym == 53)
		close_w(clear);
	return (0);
}

void	put_pixel(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
		*(unsigned int*)dst = color;
	}
}

void fu()
{
	system("leaks fdf");
}

void	init(t_vars	*vars, t_data *img)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		exit(1);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "FDF");
	if (!vars->win)
	{
		//mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(1);
	}
	img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!img->img)
	{
		mlx_destroy_window(vars->mlx, vars->mlx);
		//mlx_destroy_display(vars.mlx);
		free(vars->mlx);
		exit(1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
	vars->img = img;
}

int	check_args(int ac, char **av)
{
	int	fd;

	if (ac != 2)
	{
		ft_putendl_fd("Invalid number of argiments", 2);
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	return (fd);
}

void	*pr_malloc(size_t size, size_t type_size)
{
	if (size && SIZE_MAX / size < type_size)
		return (NULL);
	return (malloc(type_size * size));
}

void	print_map(t_map *map)
{
	int	x = 0;
	int y = 0;
	t_point **points = map->points;

	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			ft_printf("{%i,%i,%i,C:%i} ", points[y][x].x, points[y][x].y, points[y][x].z, points[y][x].color);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

void plotLine(int x0, int y0, int x1, int y1, t_data *data)
{
   int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
   int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1; 
   int err = dx+dy, e2; /* error value e_xy */
 
   for(;;){  /* loop */
      put_pixel(data, x0, y0, 0x00CCCC00);
      if (x0==x1 && y0==y1) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
   }
}
#include <math.h>

void rotateZ(int *x, int *y, float angle) {
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);
    float px = *x;
    float py = *y;

	*x = px * cosTheta - py * sinTheta;
	*y = px * sinTheta + py * cosTheta;
}

void rotateX(int *y, int *z, float angle) {
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);
    float py = *y;
    float pz = *z;

    *y = py * cosTheta - pz * sinTheta;
    *z = py * sinTheta + pz * cosTheta;
}

void rotateY(int *x, int *z, float angle) {
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);
    float px = *x;
    float pz = *z;

    *x = px * cosTheta + pz * sinTheta;
    *z = -px * sinTheta + pz * cosTheta;
}

static void iso_projection(int *x, int *y, int z)
{
    int p_x;

    p_x = *x;
    *x = (p_x - *y) * cos(0.46373398);
    *y = (p_x + *y) * sin(0.46373398) - z;
	// M_PI / 6.0
}

void isometricProjection(int *x, int *y, int z) 
{
    // Isometric projection matrix
    const float projectionMatrix[3][2] = {
        {0.7071, -0.7071},
        {0.7071, 0.7071},
        {0, 0}
    };
	int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;

    // Rotate the input point around all three axes
	// float angel = M_PI / 10;
	// rotateX(&previous_y, &z,  M_PI / 4.0);
	// rotateY(&previous_x, &z,  M_PI / 4.0);
	// rotateZ(&previous_x, &previous_y,  M_PI / 4.0);

    // Perform matrix-vector multiplication
    *x = previous_x * projectionMatrix[0][0] + previous_y * projectionMatrix[1][0];
    *y = previous_x * projectionMatrix[0][1] + previous_y * projectionMatrix[1][1];
}

// xFla = function (x, y, z) {
// 	// cartesian coordinates
// 	xCart = (x-z)*Math.cos(0.46365);
// 	// flash coordinates
// 	xI = xCart+xOrigin;
// 	return (xI);
// };
 
// // transforms x,y,z coordinates into Flash y coordinate
// yFla = function (x, y, z) {
// 	// cartesian coordinates
// 	yCart = y+(x+z)*Math.sin(0.46365);
// 	// flash coordinates
// 	yI = -yCart+yOrigin;
// 	return (yI);
// };

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

void	rotate_y(int *x, int *z, float d)
{
	int	px = *x;

	*x = px * cos(d) + *z * sin(d);
	*z = (-1*px) * sin(d) + *z * cos(d);
}

typedef struct s_position
{
	int	scale;
	int	right;
	int	top;
	int	left;
	int	bottom;
} t_position;

int	get_zmax(t_point **points, int height, int width)
{
	int	i;
	int	j;
	int z_max;

	i = 0;
	j = 0;
	z_max = 0;
	while (i < height - 1)
	{
		j = 0;
		while (j < width - 1)
		{
			if (z_max < points[i][j].z)
				z_max = points[i][j].z;
			j++;
		}
		i++;
	}
	return (z_max);
}

t_line get_line_1(int x, int y, t_point **points, t_position position)
{
	t_line	line;

	line.x1 = (x * position.scale) - position.left;
	line.y1 = (y * position.scale) - position.bottom;
	iso_projection(&line.x1, &line.y1, points[y][x].z * position.scale);
	line.x1 += position.right;
	line.y1 += position.top;
	line.x2 = ((x + 1) * position.scale) - position.left;
	line.y2 = (y * position.scale) - position.bottom;
	iso_projection(&line.x2, &line.y2, points[y][x + 1].z * position.scale);
	line.x2 += position.right;
	line.y2 += position.top;
	return (line);
}

t_line get_line_2(int x, int y, t_point **points, t_position position)
{
	t_line	line;

	line.x1 = (x * position.scale) - position.left;
	line.y1 = (y * position.scale) - position.bottom;
	iso_projection(&line.x1, &line.y1, points[y][x].z * position.scale);
	line.x1 += position.right;
	line.y1 += position.top;
	line.x2 = (x * position.scale) - position.left;
	line.y2 = ((y + 1) * position.scale) - position.bottom;
	iso_projection(&line.x2, &line.y2, points[y + 1][x].z * position.scale);
	line.x2 += position.right;
	line.y2 += position.top;
	return (line);
}

int main(int ac, char **av)
{
	//atexit(fu);
	t_vars	vars;
	t_data	img;
	t_map	*map;
	int		fd;
	t_clear	clear;

	fd = check_args(ac, av);
	map = gen_map(fd);
	if (!map)
	{
		close(fd);
		return 1;
	}
	// print_map(map);
	clear.fd = fd;
	clear.map = map;
	clear.vars = &vars;

	init(&vars, &img);
	mlx_hook(vars.win, 3, 0, key_handler, &clear);
	mlx_hook(vars.win, 17, 0, close_w, &clear);
	
	// start
	int x;
	int	y;
	t_point **points = map->points;
	t_position	position;
	position.scale = min(WIDTH / map->width / 2, HEIGHT / map->width / 2);
	position.right = WIDTH / 2 ;
	position.top =  (HEIGHT + get_zmax(points, map->height, map->width) * position.scale) / 2;
	position.left = (map->width * position.scale) / 2;
	position.bottom = (map->height * position.scale) / 2;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x != map->width - 1)
				drow_line(get_line_1(x, y, points, position), &img);
			if (y != map->height - 1)
				drow_line(get_line_2(x, y, points, position), &img);
			x++;
		}
		y++;
	}

	// end
	mlx_put_image_to_window(vars.mlx , vars.win, vars.img->img, 0, 0);
	mlx_loop(vars.mlx);
	
	clear_x(&clear);
	exit(0);
}