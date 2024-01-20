/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 21:22:06 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/20 17:30:34 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
		*(unsigned int*)dst = color;
	}
}

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

void	draw_line_1(t_delta delta, t_line line, t_data *img, unsigned int *gradient)
{
	int	i;

	delta.d = 2 * delta.dy - delta.dx;
	i = 0;
	while (i < delta.dx)
	{
		put_pixel(img, line.x1, line.y1, gradient[i]);
		line.x1 += delta.xs;
		if (delta.d < 0)
			delta.d += (2 * delta.dy);
		else
		{
			delta.d += 2 * (delta.dy - delta.dx);
			line.y1 += delta.ys;
		}
		i++;
	}
}

void	draw_line_2(t_delta delta, t_line line, t_data *img, unsigned int *gradient)
{
	int	i;

	delta.d = 2 * delta.dx - delta.dy;
	i = 0;
	while (i < delta.dy)
	{
		put_pixel(img, line.x1, line.y1, gradient[i]);
		line.y1 += delta.ys;
		if (delta.d < 0)
			delta.d += (2 * delta.dx);
		else
		{
			delta.d += 2 * (delta.dx - delta.dy);
			line.x1 += delta.xs;
		}
		i++;
	}
}

void	draw_line(t_line line, t_data *img, t_args *args)
{
	t_delta			delta;
	unsigned int	*gradient;

	slop(line, &delta);
	if (delta.dx > delta.dy)
		gradient = gen_gradient(line.color1, line.color2, delta.dx);
	else
		gradient = gen_gradient(line.color1, line.color2, delta.dy);
	if (!gradient)
		close_w(args);
	if (delta.dx > delta.dy)
		draw_line_1(delta, line, img, gradient);
	else
		draw_line_2(delta, line, img, gradient);
	free(gradient);
}

unsigned int	calc_color(double c1, double c2, double per)
{
	return (round((c1 + (c2 - c1) * per)));
}

unsigned int merge_colors(unsigned int c1, unsigned int c2, double per) 
{
	int	red;
	int	green;
	int	blue;

	red = calc_color((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, per);
	green = calc_color((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, per);
	blue = calc_color(c1 & 0xFF, c2 & 0xFF, per);
	return ((red << 16) | (green << 8) | blue);
}

unsigned int	*gen_gradient(unsigned int c1, unsigned int c2, int num) 
{
	unsigned int *gradient;
	int			i;
	double		color_per;
	int			color;

	gradient = malloc(sizeof(int) * num);
	if(!gradient)
		return (NULL);
	i = 1;
    while (i <= num) 
	{
        color_per = (double)i / num;
        color = merge_colors(c1, c2, color_per);
		gradient[i++ - 1] = color;
    }
	return (gradient);
}