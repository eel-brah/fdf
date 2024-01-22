/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:51:03 by eel-brah          #+#    #+#             */
/*   Updated: 2024/01/21 23:24:17 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

char	**get_lines(int fd)
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

t_map	*gen_map(int fd)
{
	char	**lines;
	int		y;
	t_map	*map;

	lines = get_lines(fd);
	if (!lines)
		return (NULL);
	map = map_allocation(lines);
	if (!map)
		exit(1);
	y = fill_map(map, lines);
	if (y != -1)
	{
		free_lines(lines);
		map->height = y;
		free_map(map);
		exit(1);
	}
	init_state(map);
	free_lines(lines);
	return (map);
}
