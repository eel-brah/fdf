/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 23:46:28 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/21 23:54:48 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	clear_x(t_args *args)
{
	free_map(args->map);
	close(args->fd);
	mlx_destroy_image(args->vars->mlx, args->vars->img->img);
	mlx_destroy_window(args->vars->mlx, args->vars->win);
}

int	close_w(t_args *args)
{
	clear_x(args);
	exit(1);
}

int	get_zmax(t_point **points, int height, int width)
{
	int	i;
	int	j;
	int	z_max;

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

size_t	tt_strlen(const char *s)
{
	char	*ptr;

	ptr = (char *)s;
	while (ptr && *ptr)
		ptr++;
	return (ptr - s);
}
