/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:08:47 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/22 22:29:59 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	set_background(t_data *img)
{
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(img, x, y, 0x00212529);
			x++;
		}
		y++;
	}
}

void	get_position(t_map *map)
{
	map->position.right = WIDTH / 2 + map->state.x_poz * map->state.scale;
	map->position.top = (HEIGHT + get_zmax(map->points, map->height, map->width)
			* map->state.scale) / 2 + map->state.y_poz * map->state.scale;
	map->position.left = (map->width * map->state.scale) / 2;
	map->position.bottom = (map->height * map->state.scale) / 2;
}

void	rotation(t_line *line, int *z, t_map *map, int x)
{
	if (x == 1)
	{
		rotate_x(&line->y1, z, map->state.x_rot);
		rotate_y(&line->x1, z, map->state.y_rot);
		rotate_z(&line->x1, &line->y1, map->state.z_rot);
	}
	else
	{
		rotate_x(&line->y2, z, map->state.x_rot);
		rotate_y(&line->x2, z, map->state.y_rot);
		rotate_z(&line->x2, &line->y2, map->state.z_rot);
	}
}

t_line	get_line_1(int x, int y, t_map *map,
				void (*projection)(int *, int *, int))
{
	t_line	line;
	t_point	**points;
	int		z;

	points = map->points;
	line.x1 = (x * map->state.scale) - map->position.left;
	line.y1 = (y * map->state.scale) - map->position.bottom;
	z = round((points[y][x].z * map->state.scale) / map->state.z_scale);
	line.color1 = points[y][x].color + map->state.color;
	rotation(&line, &z, map, 1);
	projection(&line.x1, &line.y1, z);
	line.x1 += map->position.right;
	line.y1 += map->position.top;
	line.x2 = ((x + 1) * map->state.scale) - map->position.left;
	line.y2 = (y * map->state.scale) - map->position.bottom;
	z = round((points[y][x + 1].z * map->state.scale) / map->state.z_scale);
	line.color2 = points[y][x + 1].color + map->state.color;
	rotation(&line, &z, map, 2);
	projection(&line.x2, &line.y2, z);
	line.x2 += map->position.right;
	line.y2 += map->position.top;
	return (line);
}

t_line	get_line_2(int x, int y, t_map *map,
				void (*projection)(int *, int *, int))
{
	t_line	line;
	t_point	**points;
	int		z;

	points = map->points;
	line.x1 = (x * map->state.scale) - map->position.left;
	line.y1 = (y * map->state.scale) - map->position.bottom;
	z = round((points[y][x].z * map->state.scale) / map->state.z_scale);
	line.color1 = points[y][x].color + map->state.color;
	rotation(&line, &z, map, 1);
	projection(&line.x1, &line.y1, z);
	line.x1 += map->position.right;
	line.y1 += map->position.top;
	line.x2 = (x * map->state.scale) - map->position.left;
	line.y2 = ((y + 1) * map->state.scale) - map->position.bottom;
	z = round((points[y + 1][x].z * map->state.scale) / map->state.z_scale);
	line.color2 = points[y + 1][x].color + map->state.color;
	rotation(&line, &z, map, 2);
	projection(&line.x2, &line.y2, z);
	line.x2 += map->position.right;
	line.y2 += map->position.top;
	return (line);
}
