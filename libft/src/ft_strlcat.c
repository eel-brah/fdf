/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:30:18 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/05 18:17:57 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	len;

	dst_len = 0;
	if (dst)
		dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize > dst_len)
		len = dst_len + src_len;
	else
		len = dstsize + src_len;
	if (dstsize < 1)
		return (len);
	dst += dst_len;
	while (*src && dst_len++ < dstsize - 1)
		*dst++ = *src++;
	*dst = '\0';
	return (len);
}
