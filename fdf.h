/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:30:34 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/12 15:28:06 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 500
# define HIGHT 500

# include <mlx.h>
# include <libc.h>
# include "libft/libft.h"

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef	struct s_map
{
	int		width;
	int		hight;
	t_point	**points;
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

typedef struct s_clear
{
	t_vars	*vars;
	t_map	*map;
	int		fd;
}	t_clear;

typedef struct s_buffer
{
	char	*buf;
	size_t	i;
}	t_buffer;

char	*get_next_line(int fd, size_t buf_size);
void	*pr_malloc(size_t size, size_t type_size);
t_map	*gen_map(int fd);
void	free_map(t_map *map);
#endif