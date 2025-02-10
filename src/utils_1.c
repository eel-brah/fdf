/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 23:47:12 by eel-brah          #+#    #+#             */
/*   Updated: 2025/02/10 13:31:15 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../platform.h"

int	min(int n1, int n2)
{
	if (n1 > n2)
		return (n2);
	return (n1);
}

int	max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
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

void	*pr_malloc(size_t size, size_t type_size)
{
	if (size && SIZE_MAX / size < type_size)
		return (NULL);
	return (malloc(type_size * size));
}
