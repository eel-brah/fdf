/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:26:07 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/03 09:45:23 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*lp;

	lp = 0;
	while (*s)
	{
		if (*s == (unsigned char)c)
			lp = (char *)s;
		s++;
	}
	if (*s == (unsigned char)c)
		lp = (char *)s;
	return (lp);
}
