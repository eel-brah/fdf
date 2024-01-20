/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_changing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:17:55 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/20 17:18:11 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	change_projection(int keysym, t_args *args)
{
	if (keysym == 35)
	{
		if (args->map->state.projection == 'p')
			args->map->state.projection = 'i';
		else
			args->map->state.projection = 'p';
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
	change_projection(keysym, args);
	draw_map(args->map, args->vars, args);
}

int	key_handler(int keysym, t_args *args)
{
	if (keysym == ESC_KEY)
		close_w(args);
	else if (keysym == ZERO_KEY1 || keysym == ZERO_KEY2)
	{
		init_state(args->map);
		draw_map(args->map, args->vars, args);
	}
	else if(keysym == SPACE_KEY)
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

int	smoothing(t_args *args)
{
	if(args->map->state.lock)
		change_state(args->map->state.keysym, args);
	return (0);
}
