/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_map_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 23:15:47 by eel-brah          #+#    #+#             */
/*   Updated: 2025/02/10 13:30:47 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../platform.h"

int	lines_count(char **lines)
{
	int	count;

	count = 0;
	while (*lines)
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

unsigned int	hex_to_int(char *h)
{
	unsigned int		nbr;
	char				*hex;
	int					i;
	char				c;

	nbr = 0;
	hex = "0123456789abcdef";
	h += 2;
	while ((*h >= '0' && *h <= '9')
		|| (*h >= 'a' && *h <= 'f')
		|| (*h >= 'A' && *h <= 'F'))
	{
		i = 0;
		c = ft_tolower(*h++);
		while (c != hex[i])
			i++;
		nbr = nbr * 16 + i;
	}
	return (nbr);
}

char	**new_line(char **lines, int l)
{
	char	**ptr;
	int		i;

	ptr = pr_malloc(l + 1, sizeof(char *));
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
