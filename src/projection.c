/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:12:12 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/23 03:56:13 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	rotate_z(int *x, int *y, float angle)
{
	float	cos_a;
	float	sin_a;
	float	px;

	cos_a = cos(angle);
	sin_a = sin(angle);
	px = *x;
	*x = round(px * cos_a - *y * sin_a);
	*y = round(px * sin_a + *y * cos_a);
}

void	rotate_x(int *y, int *z, float angle)
{
	float	cos_a;
	float	sin_a;
	float	py;

	cos_a = cos(angle);
	sin_a = sin(angle);
	py = *y;
	*y = round(py * cos_a - *z * sin_a);
	*z = round(py * sin_a + *z * cos_a);
}

void	rotate_y(int *x, int *z, float angle)
{
	float	cos_a;
	float	sin_a;
	float	px;

	cos_a = cos(angle);
	sin_a = sin(angle);
	px = *x;
	*x = round(px * cos_a + *z * sin_a);
	*z = round(-px * sin_a + *z * cos_a);
}

void	iso_projection(int *x, int *y, int z)
{
	rotate_x(y, &z, 90 * (M_PI / 180));
	rotate_y(x, &z, 45 * (M_PI / 180));
	rotate_x(y, &z, -35.264 * (M_PI / 180));
}

void	par_projection(int *x, int *y, int z)
{
	(void)x;
	(void)y;
	(void)z;
}
