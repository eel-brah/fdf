/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:30:34 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/15 21:29:05 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1000
# define HEIGHT 1000

# include <mlx.h>
# include <libc.h>
# include <math.h>
# include "libft/libft.h"

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	unsigned int	color;
}	t_point;

typedef struct s_position
{
	int	scale;
	int	right;
	int	top;
	int	left;
	int	bottom;
}	t_position;

typedef struct s_state
{
	int	x_poz;
	int	y_poz;
	int	scale;
	float		z_scale;
	float	x_rot;
	float	y_rot;
	float	z_rot;
	int		lock;
	int		keysym;
}	t_state;

typedef	struct s_map
{
	int		width;
	int		height;
	t_point	**points;
	t_state	state;
}	t_map;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars 
{
	void	*mlx;
	void	*win;
	t_data	*img;
}	t_vars;

typedef struct s_args
{
	t_vars	*vars;
	t_map	*map;
	int		fd;
}	t_args;

typedef struct s_buffer
{
	char	*buf;
	size_t	i;
}	t_buffer;

char	*get_next_line(int fd, size_t buf_size);
void	*pr_malloc(size_t size, size_t type_size);
t_map	*gen_map(int fd);
void	free_map(t_map *map);
void	put_pixel(t_data *data, int x, int y, unsigned int color);
typedef struct s_line
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	unsigned int	color1;
	unsigned int	color2;
}	t_line;

typedef struct s_delta
{
	int	dx;
	int	dy;
	int	d;
	int	xs;
	int	ys;
}	t_delta;
void	drow_line(t_line line, t_data *img);
void	draw_map(t_map *map, t_data *img, t_vars *vars);
int	min(int n1, int n2);
int	max(int n1, int n2);
unsigned int	*gen_gradient(unsigned int c1, unsigned int c2, int num);
int close_w(t_args *args);
void	init_state(t_map *map);
#endif