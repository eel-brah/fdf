/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_changing_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:17:55 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/23 07:58:54 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	change_projection(t_args *args)
{
	args->map->state.x_rot = 0;
	args->map->state.y_rot = 0;
	args->map->state.z_rot = 0;
	if (args->map->state.projection == 'p')
		args->map->state.projection = 'i';
	else
		args->map->state.projection = 'p';
	draw_map(args->map, args->vars, args);
}

void	disko(t_args *args)
{
	if (args->map->state.disko)
		args->map->state.disko = 0;
	else
		args->map->state.disko = 1;
}

void	menu(t_args *args)
{
	if (args->map->state.menu)
		args->map->state.menu = 0;
	else
		args->map->state.menu = 1;
	draw_map(args->map, args->vars, args);
}

void	change_state(int keysym, t_args *args)
{
	args->map->state.keysym = keysym;
	movement(keysym, args);
	zoom(keysym, args);
	rotate(keysym, args);
	z_scale(keysym, args);
	change_colors(keysym, args);
	draw_map(args->map, args->vars, args);
}

int	key_handler(int keysym, t_args *args)
{
	if (keysym == ESC_KEY)
		close_w(args);
	else if (keysym == ZERO_KEY || keysym == R_KEY)
	{
		init_state(args->map);
		draw_map(args->map, args->vars, args);
	}
	else if (keysym == SPACE_KEY)
	{
		if (args->map->state.lock == 0)
			args->map->state.lock = 1;
		else
			args->map->state.lock = 0;
	}
	else if (keysym == PRJ_KEY)
		change_projection(args);
	else if (keysym == DISKO_KEY)
		disko(args);
	else if (keysym == M_KEY || keysym == H_KEY || keysym == TAB_KEY)
		menu(args);
	else
		change_state(keysym, args);
	return (0);
}
