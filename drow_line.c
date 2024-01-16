/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 21:22:06 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/15 21:28:53 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	swap(int *i, int *j)
{
	int	t;
	
	t = *i;
	*i = *j;
	*j = t;
}

int	absv(int i)
{
	if (i < 0)
		i *= -1;
	return (i);
}

void slop(t_line line, t_delta *delta)
{
	delta->dx = line.x2 - line.x1;
	delta->dy = line.y2 - line.y1;
	if (delta->dx >= 0)
		delta->xs = 1;
	else
		delta->xs = -1;
	if (delta->dy >= 0)
		delta->ys = 1;
	else
		delta->ys = -1;
	delta->dx = absv(delta->dx);
	delta->dy = absv(delta->dy);
}

void	drow_line(t_line line, t_data *img)
{
	t_delta	delta;

	slop(line, &delta);
	if (delta.dx > delta.dy)
	{
		delta.d = 2 * delta.dy - delta.dx;
		for (int i = 0; i < delta.dx; i++)
		{
			put_pixel(img, line.x1, line.y1, 0x00CCCC00);
			line.x1 += delta.xs;
			if (delta.d < 0)
				delta.d += (2 * delta.dy);
			else
			{
				delta.d += 2 * (delta.dy - delta.dx);
				line.y1 += delta.ys;
			}
		}
	}
	else
	{
		delta.d = 2 * delta.dx - delta.dy;
		for (int i = 0; i < delta.dy; i++)
		{
			put_pixel(img, line.x1, line.y1, 0x00CCCC00);
			line.y1 += delta.ys;
			if (delta.d < 0)
				delta.d += (2 * delta.dx);
			else
			{
				delta.d += 2 * (delta.dx - delta.dy);
				line.x1 += delta.xs;
			}
		}
	}
}