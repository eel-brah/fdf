/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pro_tat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:12:12 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/20 17:12:23 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void rotate_z(int *x, int *y, float angle)
{
	float cos_a;
	float sin_a;
	float px;

	cos_a = cos(angle);
	sin_a = sin(angle);
	px = *x;
	*x = round(px * cos_a - *y * sin_a);
	*y = round(px * sin_a + *y * cos_a);
}

void rotate_x(int *y, int *z, float angle)
{
	float cos_a;
	float sin_a;
	float py;

	cos_a = cos(angle);
	sin_a = sin(angle);
	py = *y;
	*y = round(py * cos_a - *z * sin_a);
	*z = round(py * sin_a + *z * cos_a);
}

void rotate_y(int *x, int *z, float angle)
{
	float cos_a;
	float sin_a;
	float px;

	cos_a = cos(angle);
	sin_a = sin(angle);
	px = *x;
	*x = round(px * cos(angle) + *z * sin(angle));
	*z = round(-px * sin(angle) + *z * cos(angle));
}

void iso_projection(int *x, int *y, int z)        
{
	// *x = round((p_x - *y) * cos(M_PI / 4.0));
    // *y = round((p_x + *y - 2 * z) * (sin(M_PI / 4.0) / sqrt(2)));
	rotate_z(x, y, -1.5708);
	rotate_x(y, &z, 1.5708);
	rotate_y(x, &z, -(M_PI / 4.0));
	rotate_x(y, &z, -0.615542721);
}

void par_projection(int *x, int *y, int z)        
{
    (void)x;
	(void)y;
	(void)z;
}