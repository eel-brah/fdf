/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:30:22 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/12 16:50:38 by eel-brah         ###   ########.fr       */
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

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
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
	vars->win = mlx_new_window(vars->mlx, WIDTH, HIGHT, "FDF");
	if (!vars->win)
	{
		//mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(1);
	}
	img->img = mlx_new_image(vars->mlx, WIDTH, HIGHT);
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

	while (y < map->hight)
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

int main(int ac, char **av)
{
	atexit(fu);
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
	
	// mlx_put_image_to_window(vars.mlx , vars.win, vars.img->img, 0, 0);
	mlx_loop(vars.mlx);
	
	clear_x(&clear);
	exit(0);
}
