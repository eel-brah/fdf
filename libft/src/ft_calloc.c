/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:07:06 by eel-brah          #+#    #+#             */
/*   Updated: 2023/12/16 01:09:45 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			s;

	if (count > 0 && SIZE_MAX / count < size)
		return (NULL);
	s = count * size;
	p = malloc(s);
	if (!p)
		return (NULL);
	ft_bzero((void *)p, s);
	return ((void *)p);
}
