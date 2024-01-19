/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:51:03 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/12 15:29:52 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void print_lines(char **ptr) // m
{
	while (*ptr)
		ft_printf("%s\n", *ptr++);
}

int	lines_count(char **lines)
{
	int	count;

	count = 0;
	while(*lines)
	{
		count++;
		lines++;
	}
	return (count);
}

void	free_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines && lines[i])
		free(lines[i++]);
	free(lines);
}

void	free_map(t_map *map)
{
	int		i;
	t_point	**points;

	i = 0;
	points = map->points;
	while (i < map->height)
		free(points[i++]);
	free(points);
	free(map);
}

char	**new_line(char **lines, int l)
{
	char	**ptr;
	int		i;

	ptr = malloc(sizeof(char *) * (l + 1));
	if (!ptr)
	{
		i = 0;
		while (i < l)
			free(lines[i++]);
		free(lines);
		return (NULL);
	}
	i = 0;
	while (i < l)
	{
		ptr[i] = lines[i];
		i++;
	}
	free(lines);
	return (ptr);

}

char **get_lines(int fd)
{
	char	*line;
	char	**lines;
	int		i;

	lines = NULL;
	i = 0;
	while (1)
	{
		line = get_next_line(fd, 10);
		if (!line)
			break ;
		if (*line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		lines = new_line(lines, i);
		if (!lines)
			exit(1);
		lines[i] = line;
		i++;
	}
	lines = new_line(lines, i);
	if (!lines)
		exit(1);
	lines[i] = NULL;
	return (lines);
}

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

int	hex_to_int(char *h)
{
	int		nbr;
	char	*hex;
	int		i;
	char	c;

	nbr = 0;
	hex = "0123456789abcdef";
	h += 2;
	while ((*h >= '0' && *h <= '9') || (*h >= 'a' && *h <= 'f') || (*h >= 'A' && *h <= 'F'))
	{
		i = 0;
		c = ft_tolower(*h++);
		while (c != hex[i])
			i++;
		nbr = nbr * 16 + i;
	}
	return (nbr);
}

char	*get_color(int *color, char *s)
{
	char	**c;

	c = ft_split(s, ',');
	if(!c)
		return (NULL);
	if (lines_count(c) > 1)
	{
		if (!ft_strncmp(c[1], "0x", 2))
			*color = hex_to_int(c[1]);
		else
			*color = ft_atoi(c[1]);
	}
	else
		*color = 16777215;
	free_lines(c);
	return (s);
}

void	*fill_map_x(t_point **points, int y, int width, char **s)
{
	int		x;

	points[y] = malloc(sizeof(t_point) * width);
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
		if (!get_color(&(points[y][x].color), s[x]))
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

t_map	*map_allocation(char **lines)
{
	t_map	*map;

	map = pr_malloc(1, sizeof(t_map));
	if (!map)
	{
		free_lines(lines);
		return (NULL);
	}
	map->height = lines_count(lines);
	map->points = pr_malloc(map->height, sizeof(t_point *));
	if (!map->points || !map->height)
	{
		if (!map->height)
			ft_printf("Invalid map\n");
		free(map->points);
		free_lines(lines);
		free(map);
		return (NULL);
	}
	return (map);
}

void	init_state(t_map *map)
{
	map->state.x_poz = 0;
	map->state.y_poz = 0;
	map->state.scale = min(WIDTH / map->width / 2, HEIGHT / map->width / 2);
	map->state.x_rot = 0;
	map->state.y_rot = 0;
	map->state.z_rot = 0;
}

t_map *gen_map(int fd)
{
	char	**lines;
	int		y;
	t_map	*map;

	lines = get_lines(fd);
	if (!lines)
		return (NULL);
	// print_lines(lines); // kkl
	map = map_allocation(lines);
	if (!map)
		return (NULL);
	y = fill_map(map, lines);
	if (y != -1)
	{
		free_lines(lines);
		map->height = y;
		free_map(map);
		return (NULL);
	}
	init_state(map);
	free_lines(lines); 
	return (map);
}
