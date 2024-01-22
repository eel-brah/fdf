/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:30:34 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/22 01:40:18 by eel-brah         ###   ########.fr       */
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
# define DISKO_KEY 40
# define PRJ_KEY 35
# define COLOR_C_KEY 8
# define COLOR_V_KEY 9
# define ZOOM_IN_1_KEY 34
# define ZOOM_OUT_1_KEY 31
# define ZOOM_IN_2_KEY 69
# define ZOOM_OUT_2_KEY 78
# define Z_UP_KEY 24
# define Z_DOWN_KEY 27
# define UP_KEY 126
# define DOWN_KEY 125
# define RIGHT_KEY 124
# define LEFT_KEY 123
# define UP_W_KEY 13
# define DOWN_S_KEY 1
# define RIGHT_D_KEY 2
# define LEFT_S_KEY 0
# define RRX_KEY 18
# define RLX_KEY 19
# define RRY_KEY 20
# define RLY_KEY 21
# define RRZ_KEY 23
# define RLZ_KEY 22
# define RRX2_KEY 83
# define RLX2_KEY 84
# define RRY2_KEY 85
# define RLY2_KEY 86
# define RRZ2_KEY 87
# define RLZ2_KEY 88

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

 void	print_map(t_map *map);
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


t_map			*gen_map(int fd);
void			free_map(t_map *map);
int				lines_count(char **lines);
void			free_lines(char **lines);
unsigned int	hex_to_int(char *h);
char			**new_line(char **lines, int l);
int				fill_map(t_map *map, char **lines);
void			init_state(t_map *map);
int				smoothing(t_args *args);
int				key_handler(int keysym, t_args *args);
void			change_state(int keysym, t_args *args);
void			change_projection(int keysym, t_args *args);
void			change_colors(int keysym, t_args *args);
void			zoom(int keysym, t_args *args);
void			z_scale(int keysym, t_args *args);
void			rotate(int keysym, t_args *args);
void			movement(int keysym, t_args *args);
int				get_zmax(t_point **points, int height, int width);
void			draw_line(t_line line, t_data *img, t_args *args);
void			draw_map(t_map *map, t_vars *vars, t_args *args);
unsigned int	*gen_gradient(unsigned int c1, unsigned int c2, int num);
void			put_pixel(t_data *data, int x, int y, unsigned int color);
char			*get_next_line(int fd, size_t buf_size);
void			rotate_x(int *y, int *z, float angle);
void			rotate_y(int *x, int *z, float angle);
void			rotate_z(int *x, int *y, float angle);
void			iso_projection(int *x, int *y, int z);
void			par_projection(int *x, int *y, int z);
void			set_background(t_data *img);
void			get_position(t_map *map);
t_line 			get_line_2(int x, int y, t_map *map,
				void (*projection)(int *, int *, int));
t_line 			get_line_1(int x, int y, t_map *map,
				void (*projection)(int *, int *, int));
int				absv(int i);
int 			close_w(t_args *args);
void			clear_x(t_args *args);
size_t			tt_strlen(const char *s);
void	*pr_malloc(size_t size, size_t type_size);


int	min(int n1, int n2);
int	max(int n1, int n2);



#endif