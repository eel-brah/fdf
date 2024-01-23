/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_changing_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 23:31:22 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/23 03:55:44 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	movement(int keysym, t_args *args)
{
	if (keysym == LEFT_KEY || keysym == LEFT_S_KEY)
		args->map->state.x_poz--;
	else if (keysym == RIGHT_KEY || keysym == RIGHT_D_KEY)
		args->map->state.x_poz++;
	else if (keysym == DOWN_KEY || keysym == DOWN_S_KEY)
		args->map->state.y_poz++;
	else if (keysym == UP_KEY || keysym == UP_W_KEY)
		args->map->state.y_poz--;
}

void	rotate(int keysym, t_args *args)
{
	if (args->map->state.disko)
		args->map->state.color += 1000;
	if (keysym == RRX_KEY || keysym == RRX2_KEY)
		args->map->state.x_rot += 0.01;
	if (keysym == RLX_KEY || keysym == RLX2_KEY)
		args->map->state.x_rot -= 0.01;
	if (keysym == RRY_KEY || keysym == RRY2_KEY)
		args->map->state.y_rot += 0.01;
	if (keysym == RLY_KEY || keysym == RLY2_KEY)
		args->map->state.y_rot -= 0.01;
	if (keysym == RRZ_KEY || keysym == RRZ2_KEY)
		args->map->state.z_rot += 0.01;
	if (keysym == RLZ_KEY || keysym == RLZ2_KEY)
		args->map->state.z_rot -= 0.01;
}

void	z_scale(int keysym, t_args *args)
{
	if ((keysym == Z_UP_KEY || keysym == Z_UP_KEY_2)
		&& args->map->state.z_scale < 20)
		args->map->state.z_scale += 0.1;
	if ((keysym == Z_DOWN_KEY || keysym == Z_DOWN_KEY_2)
		&& args->map->state.z_scale > 1)
		args->map->state.z_scale -= 0.1;
}

void	zoom(int keysym, t_args *args)
{
	if (keysym == ZOOM_IN_KEY)
		args->map->state.scale++;
	if ((keysym == ZOOM_OUT_KEY) && args->map->state.scale > 1)
		args->map->state.scale--;
}

void	change_colors(int keysym, t_args *args)
{
	int	r;

	r = 1000;
	if (COLOR_C_KEY == keysym || COLOR_V_KEY == keysym)
	{
		if (COLOR_V_KEY == keysym)
			r *= -1;
		args->map->state.color += r;
	}
}
