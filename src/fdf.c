/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:30:22 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/23 09:48:40 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	init(t_vars	*vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		ft_putendl_fd("MLX faild", 2);
		exit(1);
	}
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "FDF");
	if (!vars->win)
	{
		ft_putendl_fd("MLX faild", 2);
		exit(1);
	}
	vars->img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->img->img)
	{
		mlx_destroy_window(vars->mlx, vars->mlx);
		exit(1);
	}
	vars->img->addr = mlx_get_data_addr(vars->img->img,
			&vars->img->bpp, &vars->img->line_length, &vars->img->endian);
}

int	check_args(int ac, char **av)
{
	int	fd;

	if (ac != 2)
	{
		ft_putstr_fd("Invalid number of argiments\n./fdf map\n", 2);
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

void	draw_map_helper(t_map *map, t_vars *vars)
{
	if (!map->state.menu)
		draw_pre_menu(vars);
	if (map->state.menu)
		draw_menu(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	if (map->state.menu)
		menu_text(vars);
	if (!map->state.menu)
		pre_menu_text(vars);
}

void	draw_map(t_map *map, t_vars *vars, t_args *args)
{
	int			x;
	int			y;
	void		(*projection)(int *, int *, int);

	set_background(vars->img);
	get_position(map);
	if (map->state.projection == 'p')
		projection = par_projection;
	else
		projection = iso_projection;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x != map->width - 1)
				draw_line(get_line_1(x, y, map, projection), vars->img, args);
			if (y != map->height - 1)
				draw_line(get_line_2(x, y, map, projection), vars->img, args);
			x++;
		}
		y++;
	}
	draw_map_helper(map, vars);
}

int	main(int ac, char **av)
{
	t_vars	vars;
	t_data	img;
	t_args	args;

	vars.img = &img;
	args.vars = &vars;
	args.fd = check_args(ac, av);
	args.map = gen_map(args.fd);
	if (!args.map)
	{
		close(args.fd);
		exit(1);
	}
	init(&vars);
	mlx_hook(vars.win, 2, 0, key_handler, &args);
	mlx_hook(vars.win, 17, 0, close_w, &args);
	mlx_loop_hook(vars.mlx, animation, &args);
	draw_map(args.map, &vars, &args);
	ft_printf("\033[4;35m\033[1;95mFDF\033[0m \033[0;95mRunning...\033[0m\n");
	mlx_loop(vars.mlx);
	clear_x(&args);
	exit(0);
}
