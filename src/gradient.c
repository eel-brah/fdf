/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 23:42:48 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/23 04:03:11 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

unsigned int	calc_color(double c1, double c2, double per)
{
	return (round((c1 + (c2 - c1) * per)));
}

unsigned int	merge_colors(unsigned int c1, unsigned int c2, double per)
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
	unsigned int	*gradient;
	int				i;
	double			color_per;
	int				color;

	gradient = pr_malloc(num, sizeof(int));
	if (!gradient)
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
