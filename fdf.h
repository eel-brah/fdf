/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:30:34 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/12 11:37:08 by eel-brah         ###   ########.fr       */
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
	int	width;
	int	hight;
	t_point point;
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

typedef struct s_buffer
{
	char	*buf;
	size_t	i;
}	t_buffer;

char	*get_next_line(int fd, size_t buf_size);

#endif