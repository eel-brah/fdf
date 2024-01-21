/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:30:34 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/21 20:26:28 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1000
# define HEIGHT 1000
# define ESC_KEY 53
# define ZERO_KEY1 82
# define ZERO_KEY2 15
# define SPACE_KEY 49
 
# include <mlx.h>
# include <libc.h>
# include <math.h>
# include "../libft/libft.h"

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	unsigned int	color;
}	t_point;

typedef struct s_position
{
	int	right;
	int	top;
	int	left;
	int	bottom;
}	t_position;

typedef struct s_state
{
	int		x_poz;
	int		y_poz;
	int		scale;
	float	z_scale;
	float	x_rot;
	float	y_rot;
	float	z_rot;
	int		lock;
	int		keysym;
	char	projection;
	int		disko;
	int		color;
}	t_state;

typedef	struct s_map
{
	int			width;
	int			height;
	t_point		**points;
	t_state		state;
	t_position	position;
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
void	draw_line(t_line line, t_data *img, t_args *args);
void	draw_map(t_map *map, t_vars *vars, t_args *args);
unsigned int	*gen_gradient(unsigned int c1, unsigned int c2, int num);
int close_w(t_args *args);
void	clear_x(t_args *args);
void	init_state(t_map *map);
void	put_pixel(t_data *data, int x, int y, unsigned int color);


void rotate_x(int *y, int *z, float angle);
void rotate_y(int *x, int *z, float angle);
void rotate_z(int *x, int *y, float angle);
void iso_projection(int *x, int *y, int z);
void par_projection(int *x, int *y, int z);

void	set_background(t_data *img);
void	get_position(t_map *map);
t_line get_line_2(int x, int y, t_map *map,
				void (*projection)(int *, int *, int));
t_line get_line_1(int x, int y, t_map *map,
				void (*projection)(int *, int *, int));

int	min(int n1, int n2);
int	max(int n1, int n2);

int		smoothing(t_args *args);
int		key_handler(int keysym, t_args *args);
void	change_state(int keysym, t_args *args);
void	change_projection(int keysym, t_args *args);
void	change_colors(int keysym, t_args *args);
void	zoom(int keysym, t_args *args);
void	z_scale(int keysym, t_args *args);
void	rotate(int keysym, t_args *args);
void	movement(int keysym, t_args *args);

#endif