/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:30:22 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/12 11:32:26 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_x(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	//mlx_destroy_display(vars.mlx);
	// free(vars->mlx);
}

int close_w(t_vars *vars)
{
	clear_x(vars);
	exit(0);
}

int	key_handler(int keysym, t_vars *vars)
{
	if (keysym == 53)
		close_w(vars);
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

typedef struct s_pixel
{
	int	pos;
	int	color;
}	t_pixel;

char	**new_line(char **lines, int l)
{
	char	**ptr;
	int		i;

	ptr = malloc(sizeof(char *) * (l + 1));
	if (!ptr)
	{
		i = 0;
		while (i < l)
			free(lines[i++]);
		free(lines);
		return (NULL);
	}
	i = 0;
	while (i < l)
	{
		ptr[i] = lines[i];
		i++;
	}
	free(lines);
	return (ptr);

}

char **get_lines(int fd)
{
	char	*line;
	char	**lines;
	int		i;

	lines = NULL;
	i = 0;
	while (1)
	{
		line = get_next_line(fd, 10);
		if (!line)
			break ;
		if (*line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		lines = new_line(lines, i);
		if (!lines)
			exit(1);
		lines[i] = line;
		i++;
	}
	lines = new_line(lines, i);
	if (!lines)
		exit(1);
	lines[i] = NULL;
	return (lines);
}

void	*pr_malloc(size_t size, size_t type_size)
{
	if (size && SIZE_MAX / size < type_size)
		return (NULL);
	return (malloc(type_size * size));
}

void	free_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines && lines[i])
		free(lines[i++]);
	free(lines);
}

void	free_map(t_point **map, int y)
{
	int	i;

	i = 0;
	while (i < y)
		free(map[i++]);
	free(map);
}

void print_lines(char **ptr)
{
	while (*ptr)
		ft_printf("%s\n", *ptr++);
}

int	lines_count(char **lines)
{
	int	count;

	count = 0;
	while(*lines)
	{
		count++;
		lines++;
	}
	return (count);
}

char	**split_line(char *line, int *len)
{
	char	**s;

	s = ft_split(line, ' '); 
	if (!s)
		return (NULL);
	*len = 0;
	while (s[*len])
		(*len)++;
	if (!*len)
	{
		free(s);
		return (NULL); 
	}
	return (s);
}

void	print_map(t_point **map, int y_len, int x_len)
{
	int	x = 0;
	int y = 0;
	while (y < y_len)
	{
		x = 0;
		while (x < x_len)
		{
			ft_printf("{%i,%i,%i,C:%i} ", map[y][x].x, map[y][x].y, map[y][x].z, map[y][x].color);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

int	hex_to_int(char *h)
{
	int		nbr;
	char	*hex;
	int		i;
	char	c;

	nbr = 0;
	hex = "0123456789abcdef";
	h += 2;
	while ((*h >= '0' && *h <= '9') || (*h >= 'a' && *h <= 'f') || (*h >= 'A' && *h <= 'F'))
	{
		i = 0;
		c = ft_tolower(*h++);
		while (c != hex[i])
			i++;
		nbr = nbr * 16 + i;
	}
	return (nbr);
}

char	*get_color(int *color, char *s)
{
	char	**c;

	c = ft_split(s, ',');
	if(!c)
		return (NULL);
	if (lines_count(c) > 1)
	{
		if (!ft_strncmp(c[1], "0x", 2))
			*color = hex_to_int(c[1]);
		else
			*color = ft_atoi(c[1]);
	}
	else
		*color = 16777215;
	free_lines(c);
	return (s);
}

void	*fill_map_x(t_point **map, int y, int x_len, char **s)
{
	int		x;

	map[y] = malloc(sizeof(t_point) * x_len);
	if (!map[y])
	{
		free_lines(s);
		return (NULL);
	}
	x = 0;
	while (x < x_len)
	{
		map[y][x].x = x;
		map[y][x].y = y;
		map[y][x].z = ft_atoi(s[x]);
		if (!get_color(&(map[y][x].color), s[x]))
		{
			free_lines(s);
			return (NULL);
		}
		x++;
	}
	free_lines(s);
	return (map);
}

int	fill_map(t_point **map, char **lines)
{
	char	**s;
	int		x_len;
	int		y;
	int		x_len_tmp;

	y = 0;
	s = split_line(*lines, &x_len);
	if (!s)
		return (y);
	while (lines[y])
	{
		if (y)
		{
			s = split_line(lines[y], &x_len_tmp);
			if (x_len_tmp < x_len || !s)
			{
				free_lines(s);
				return (y);
			}
		}
		if (!fill_map_x(map, y, x_len, s))
			return (++y);
		y++;
	}
	print_map(map, y, x_len);
	return (-1);
}

t_point	**gen_map(int fd)
{
	t_point	**map;
	char	**lines;
	int		y_len;
	int		y;

	lines = get_lines(fd);
	if (!lines)
		return (NULL);
	print_lines(lines); // kkl
	y_len = lines_count(lines);
	map = pr_malloc(y_len, sizeof(t_point *));
	if (!map || !y_len)
	{
		free(map);
		free_lines(lines);
		return (NULL);
	}
	y = fill_map(map, lines);
	if (y != -1)
	{
		free_lines(lines);
		free_map(map, y);
		return (NULL);
	}
	free_lines(lines); 
	free_map(map, y_len);
	return (map);
}

int main(int ac, char **av)
{
	atexit(fu);
	t_vars	vars;
	t_data	img;
	t_point	**map;
	int		fd;

	fd = check_args(ac, av);
	map = gen_map(fd);
	
	

	close(fd);
	return 0;
	init(&vars, &img);
	
	mlx_hook(vars.win, 3, 0, key_handler, &vars);
	mlx_hook(vars.win, 17, 0, close_w, &vars);

	
	mlx_put_image_to_window(vars.mlx , vars.win, vars.img->img, 0, 0);
	mlx_loop(vars.mlx);
	
	clear_x(&vars);
	exit(0);
}
