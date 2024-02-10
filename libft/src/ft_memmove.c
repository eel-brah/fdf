/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:07:01 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/03 09:58:08 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*s;
	unsigned char		*d;
	const unsigned char	*end;

	if (!src && !dst)
		return (NULL);
	s = src;
	d = dst;
	if (s > d)
	{
		end = s + len;
		while (s < end)
			*d++ = *s++;
	}
	else
	{
		end = s;
		d = d + len - 1;
		s = s + len - 1;
		while (s >= end)
			*d-- = *s--;
	}
	return (dst);
}
