/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 01:52:28 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/23 02:32:22 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	draw_pre_menu(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < 40)
	{
		x = 0;
		while(x < 165)
		{
			put_pixel(vars->img, x, y, 0x191c1f);
			x++;
		}
		y++;
	}
}

void	pre_menu_text(t_vars *vars)
{
	mlx_string_put(vars->mlx, vars->win, 10, 10, 0x999999, "Usage: Tab / m");
}

void	draw_menu(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < 660)
	{
		x = 0;
		while(x < 190)
		{
			put_pixel(vars->img, x, y, 0x191c1f);
			x++;
		}
		y++;
	}
}

void	menu_text_2(int x, int y, t_vars *vars)
{
	mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Z_scale:");
	mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "- +");
	y += 30 + 20;
	mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Projection:");
	mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "p");
	y += 30 + 20;
	mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Color:");
	mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "c v");
	y += (30 + 20);
	mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Start / Stop:");
	mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "space");
	y += (30 + 20);
	mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Disko:");
	mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "k");
	y += (30 + 20);
	mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Reset:");
	mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "0");
	y += (30 + 20);
	mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Hide / Show Menu:");
	mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "Tab or m");
}

void	menu_text(t_vars *vars)
{
	int x;
	int	y;
	
	x = 10;
	y = 50;
	mlx_string_put(vars->mlx, vars->win, x + 30, y - 30, TEXT_COLOR_2, "How To Use");
	mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Exit:");
	mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "esc");
	y += (30 + 20);
	mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Zoom:");
	mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "In i or +");
	mlx_string_put(vars->mlx, vars->win, x, y + 40, TEXT_COLOR_2, "Out o or -");
	y += (30 + 40);
	mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Movement:");
	mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "Arrows or WASD");
	y += (30 + 20);
	mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, "Rotatation:");
	mlx_string_put(vars->mlx, vars->win, x, y + 20, TEXT_COLOR_2, "x-axis 1 2");
	mlx_string_put(vars->mlx, vars->win, x, y + 40, TEXT_COLOR_2, "y-axis 3 4");
	mlx_string_put(vars->mlx, vars->win, x, y + 60, TEXT_COLOR_2, "z-axis 5 6");
	y += (30 + 60);
	menu_text_2(x, y, vars);
}
