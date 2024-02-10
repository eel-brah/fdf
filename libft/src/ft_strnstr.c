/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:31:03 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/05 18:26:39 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char		*p;
	const char		*n;
	const char		*t;
	unsigned int	i;

	p = haystack;
	n = needle;
	if (!*n)
		return ((char *)p);
	if (!p && !len)
		return (NULL);
	while (*p && len)
	{
		n = needle;
		t = p;
		i = len;
		while (*n == *p++ && *n && i--)
			n++;
		if (!*n)
			return ((char *)t);
		p = t + 1;
		len--;
	}
	return (NULL);
}
