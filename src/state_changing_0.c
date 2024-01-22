/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_changing_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:17:55 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/22 00:57:18 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	change_projection(int keysym, t_args *args)
{
	if (keysym == PRJ_KEY)
	{
		if (args->map->state.projection == 'p')
			args->map->state.projection = 'i';
		else
			args->map->state.projection = 'p';
	}
}

void	disko(int keysym, t_args *args)
{
	if (keysym == DISKO_KEY)
	{
		if (args->map->state.disko)
			args->map->state.disko = 0;
		else
			args->map->state.disko = 1;
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
	disko(keysym, args);
	draw_map(args->map, args->vars, args);
}

int	key_handler(int keysym, t_args *args)
{
	ft_printf("%i\n", keysym);
	if (keysym == ESC_KEY)
		close_w(args);
	else if (keysym == ZERO_KEY1 || keysym == ZERO_KEY2)
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
	else
		change_state(keysym, args);
	return (0);
}

int	smoothing(t_args *args)
{
	if (args->map->state.lock)
		change_state(args->map->state.keysym, args);
	return (0);
}
