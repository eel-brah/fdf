/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_map_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 23:22:50 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/23 04:03:52 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

char	**split_line(char *line, int *len, int width)
{
	char	**s;

	s = ft_split(line, ' ');
	if (!s)
		return (NULL);
	*len = 0;
	while (s[*len])
		(*len)++;
	if (!*len || *len < width)
	{
		ft_printf("Invalid map\n");
		free_lines(s);
		return (NULL);
	}
	return (s);
}

char	*get_color(unsigned int *color, int z, char *s)
{
	char	**c;

	c = ft_split(s, ',');
	if (!c)
		return (NULL);
	if (lines_count(c) > 1)
	{
		if (!ft_strncmp(c[1], "0x", 2))
			*color = hex_to_int(c[1]);
		else
			*color = (unsigned int)ft_atoi(c[1]);
	}
	else if (z > 0)
		*color = DEF_COLOR;
	else
		*color = DEF_COLOR_2;
	free_lines(c);
	return (s);
}

void	*fill_map_x(t_point **points, int y, int width, char **s)
{
	int		x;

	points[y] = pr_malloc(width, sizeof(t_point));
	if (!points[y])
	{
		free_lines(s);
		return (NULL);
	}
	x = 0;
	while (x < width)
	{
		points[y][x].x = x;
		points[y][x].y = y;
		points[y][x].z = ft_atoi(s[x]);
		if (!get_color(&(points[y][x].color), points[y][x].z, s[x]))
		{
			free_lines(s);
			return (NULL);
		}
		x++;
	}
	free_lines(s);
	return (points);
}

int	fill_map(t_map *map, char **lines)
{
	char	**s;
	int		x_len;
	int		y;

	y = 0;
	s = split_line(*lines, &(map->width), 0);
	if (!s)
		return (y);
	while (lines[y])
	{
		if (y)
		{
			s = split_line(lines[y], &x_len, map->width);
			if (x_len < map->width || !s)
				return (y);
		}
		if (!fill_map_x(map->points, y, map->width, s))
			return (++y);
		y++;
	}
	return (-1);
}

void	init_state(t_map *map)
{
	map->state.x_poz = 0;
	map->state.y_poz = 0;
	map->state.scale = max(min(WIDTH / map->width / 2,
				HEIGHT / map->height / 2), 1);
	map->state.z_scale = 1;
	map->state.x_rot = 0;
	map->state.y_rot = 0;
	map->state.z_rot = 0;
	map->state.lock = 0;
	map->state.keysym = 47;
	map->state.projection = 'i';
	map->state.color = 0;
	map->state.disko = 0;
	map->state.menu = 0;
}
