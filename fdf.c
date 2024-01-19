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

void	clear_x(t_args *args)
{
	free_map(args->map);
	close(args->fd);
	mlx_destroy_image(args->vars->mlx, args->vars->img->img);
	mlx_destroy_window(args->vars->mlx, args->vars->win);
	//mlx_destroy_display(args->vars.mlx);
	// free(args->vars->mlx);
}

int close_w(t_args *args)
{
	clear_x(args);
	exit(0);
}

void	movement(int keysym, t_args *args)
{
	if (keysym == 123 || keysym == 0)
		args->map->state.x_poz--;
	else if (keysym == 124 || keysym == 2)
		args->map->state.x_poz++;
	else if (keysym == 125 || keysym == 13)
		args->map->state.y_poz++;
	else if (keysym == 126 || keysym == 1)
		args->map->state.y_poz--;
}

void	rotate(int keysym, t_args *args)
{
	if (keysym == 18 || keysym == 83)
		args->map->state.x_rot += 0.01;
	if (keysym == 19 || keysym == 84)
		args->map->state.x_rot -= 0.01;
	if (keysym == 20 || keysym == 85)
		args->map->state.y_rot += 0.01;
	if (keysym == 21 || keysym == 86)
		args->map->state.y_rot -= 0.01;
	if (keysym == 23 || keysym == 87)
		args->map->state.z_rot += 0.01;
	if (keysym == 22 || keysym == 88)
		args->map->state.z_rot -= 0.01;
}

void	z_scale(int keysym, t_args *args)
{
	if (keysym == 24 && args->map->state.z_scale < 20)
		args->map->state.z_scale += 0.1;
	if (keysym == 27 && args->map->state.z_scale > 1)
		args->map->state.z_scale -= 0.1;
}
void	zoom(int keysym, t_args *args)
{
	if (keysym == 34 || keysym == 69)
		args->map->state.scale++;
	if ((keysym == 31 || keysym == 78) && args->map->state.scale > 1)
		args->map->state.scale--;
}

void	change_colors(int keysym, t_args *args)
{
	int	i;
	int	j;
	int r;

	r = 1000;
	i = 0;
	if (keysym == 8 || keysym == 9)
	{
		if (keysym == 9)
			r *= -1;
		while (i < args->map->height)
		{
			j = 0;
			while (j < args->map->width)
				args->map->points[i][j++].color += r; 
			i++;
		}
	}
}

void	change_state(int keysym, t_args *args)
{
	args->map->state.keysym = keysym;
	movement(keysym, args);
	zoom(keysym, args);
	rotate(keysym, args);
	z_scale(keysym, args);
	change_colors(keysym, args);
	
	ft_printf("%i\n", keysym);
	draw_map(args->map, args->vars->img, args->vars);
}

int	key_handler(int keysym, t_args *args)
{
	ft_printf("%i\n", keysym);
	if (keysym == 53)
		close_w(args);
	else if (keysym == 82 || keysym == 15)
	{
		init_state(args->map);
		draw_map(args->map, args->vars->img, args->vars);
	}
	else if(keysym == 49)
	{
		if (args->map->state.lock == 0)
			args->map->state.lock = 1;
		else
			args->map->state.lock = 0;
	}
	else
		change_state(keysym, args);
	return (0);
}

// int	key_press(int keysym, t_args *args)
// {
// 	if (keysym == 53)
// 		close_w(args);
// 	args->map->state.keysym = keysym;
// 	args->map->state.changing = 1;
// 	return (0);
// }

// int	key_release(int keysym, t_args *args)
// {
// 	if (keysym == 53)
// 		close_w(args);
// 	// args->map->state.keysym = keysym;
// 	args->map->state.changing = 0;
// 	return (0);
// }

int	smoothing(t_args *args)
{
	if(args->map->state.lock)
		change_state(args->map->state.keysym, args);
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

void rotate_z(int *x, int *y, float angle) {
    float cos_a = cos(angle);
    float sin_a = sin(angle);
    float px = *x;
    float py = *y;

	*x = round(px * cos_a - py * sin_a);
	*y = round(px * sin_a + py * cos_a);
}

void rotate_x(int *y, int *z, float angle) {
    float cos_a = cos(angle);
    float sin_a = sin(angle);
    float py = *y;
    float pz = *z;

    *y = round(py * cos_a - pz * sin_a);
    *z = round(py * sin_a + pz * cos_a);
}

void rotate_y(int *x, int *z, float angle) {
    float cos_a = cos(angle);
    float sin_a = sin(angle);
    float px = *x;
    float pz = *z;

    *x = round(px * cos_a + pz * sin_a);
    *z = round(-px * sin_a + pz * cos_a);
}

void iso_projection(int *x, int *y, int z)
{
    int p_x;

    p_x = *x;
	rotate_z(&p_x, y, -1.58);
	// *x= p_x - *y;
    // *y= round((p_x + *y) / 2.0 - z);
    // *x = (p_x - *y) * cos(0.46373398);
    // *y = (p_x + *y) * sin(0.46373398) - z;
	*x = round((double)(p_x - *y) * cos(M_PI / 4.0));
    *y = round((double)(p_x + *y - 2 * z) * (sin(M_PI / 4.0) / sqrt(2)));
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

int	get_zmax(t_point **points, int height, int width)
{
	int	i;
	int	j;
	int z_max;

	i = 0;
	j = 0;
	z_max = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (z_max < points[i][j].z)
				z_max = points[i][j].z;
			j++;
		}
		i++;
	}
	return (z_max);
}

t_line get_line_1(int x, int y, t_map *map, t_position position)
{
	t_line	line;
	t_point	**points;
	int		z;

	points = map->points;
	line.x1 = (x * map->state.scale) - position.left;
	line.y1 = (y * map->state.scale) - position.bottom;
	z = round((points[y][x].z * map->state.scale) / map->state.z_scale);
	line.color1 = points[y][x].color;
	rotate_x(&line.y1, &z, map->state.x_rot);
	rotate_y(&line.x1, &z, map->state.y_rot);
	rotate_z(&line.x1, &line.y1, map->state.z_rot);
	iso_projection(&line.x1, &line.y1, z);
	line.x1 += position.right;
	line.y1 += position.top;
	line.x2 = ((x + 1) * map->state.scale) - position.left;
	line.y2 = (y * map->state.scale) - position.bottom;
	z = round((points[y][x + 1].z * map->state.scale) / map->state.z_scale);
	line.color2 = points[y][x + 1].color;
	rotate_x(&line.y2, &z, map->state.x_rot);
	rotate_y(&line.x2, &z, map->state.y_rot);
	rotate_z(&line.x2, &line.y2, map->state.z_rot);
	iso_projection(&line.x2, &line.y2, z);
	line.x2 += position.right;
	line.y2 += position.top;
	return (line);
}

t_line get_line_2(int x, int y, t_map *map, t_position position)
{
	t_line	line;
	t_point	**points;
	int		z;

	points = map->points;
	line.x1 = (x * map->state.scale) - position.left;
	line.y1 = (y * map->state.scale) - position.bottom;
	z = round((points[y][x].z * map->state.scale) / map->state.z_scale);
	line.color1 = points[y][x].color;
	rotate_x(&line.y1, &z, map->state.x_rot);
	rotate_y(&line.x1, &z, map->state.y_rot);
	rotate_z(&line.x1, &line.y1, map->state.z_rot);
	iso_projection(&line.x1, &line.y1, z);
	line.x1 += position.right;
	line.y1 += position.top;
	line.x2 = (x * map->state.scale) - position.left;
	line.y2 = ((y + 1) * map->state.scale) - position.bottom;
	z = round((points[y + 1][x].z * map->state.scale) / map->state.z_scale);
	line.color2 = points[y + 1][x].color;
	rotate_x(&line.y2, &z, map->state.x_rot);
	rotate_y(&line.x2, &z, map->state.y_rot);
	rotate_z(&line.x2, &line.y2, map->state.z_rot);
	iso_projection(&line.x2, &line.y2, z);
	line.x2 += position.right;
	line.y2 += position.top;
	return (line);
}

void	background(t_map *map, t_data *img)
{
	int x;
	int	y;
	t_point **points = map->points;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(img, x, y, 0x000b090a);
			x++;
		}
		y++;
	}
}

void	get_position(t_position *position, t_map *map)
{
	position->right = WIDTH / 2 + map->state.x_poz * map->state.scale;
	position->top =  (HEIGHT + get_zmax(map->points, map->height, map->width) * map->state.scale) / 2 + map->state.y_poz * map->state.scale;
	position->left = (map->width * map->state.scale) / 2;
	position->bottom = (map->height * map->state.scale) / 2;
}

void	draw_map(t_map *map, t_data *img, t_vars *vars)
{
	int			x;
	int			y;
	t_position	position;

	background(map, img);
	get_position(&position, map);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x != map->width - 1)
				drow_line(get_line_1(x, y, map, position), img);
			if (y != map->height - 1)
				drow_line(get_line_2(x, y, map, position), img);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx , vars->win, vars->img->img, 0, 0);
}

int main(int ac, char **av)
{
	// atexit(fu);
	t_vars	vars;
	t_data	img;
	t_map	*map;
	int		fd;
	t_args	args;

	fd = check_args(ac, av);
	map = gen_map(fd);
	if (!map)
	{
		close(fd);
		return 1;
	}
	// print_map(map);
	args.fd = fd;
	args.map = map;
	args.vars = &vars;

	init(&vars, &img);
	mlx_hook(vars.win, 2, 0, key_handler, &args);
	// mlx_hook(vars.win, 3, 0, key_release, &args);

	mlx_hook(vars.win, 17, 0, close_w, &args);
	mlx_loop_hook(vars.mlx, smoothing, &args);

	draw_map(map, &img, &vars);
	mlx_loop(vars.mlx);
	clear_x(&args);
	exit(0);
}
