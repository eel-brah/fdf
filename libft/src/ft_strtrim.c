/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:30:21 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/04 12:11:18 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	size_t	len;
	char	*ptr;
	int		sur;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	sur = 0;
	while (len && *(s1 + len - 1 - sur) && ft_strchr(set, *(s1 + len -1 - sur)))
		sur++;
	size = len - sur + 1;
	ptr = malloc(sizeof(char) * size);
	if (!ptr)
		return (NULL);
	ft_strlcpy (ptr, s1, size);
	return (ptr);
}
