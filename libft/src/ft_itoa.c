/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:59:19 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/02 13:38:24 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*ft_itoa_fill(char *nbr, unsigned int n, int len, int sign)
{
	nbr[len] = '\0';
	while (len)
	{
		nbr[--len] = n % 10 + 48;
		n /= 10;
	}
	if (sign)
		nbr[len] = '-';
	return (nbr);
}

static int	ft_itoa_count(unsigned int nb)
{
	int	len;

	len = 0;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	len;
	unsigned int	nb;
	char			*nbr;
	int				sign;

	sign = 0;
	nb = n;
	if (n < 0)
	{
		nb *= -1;
		sign = 1;
	}
	len = ft_itoa_count(nb) + sign;
	if (n == 0)
		len = 1;
	nbr = malloc(sizeof(char) * (len + 1));
	if (!nbr)
		return (NULL);
	return (ft_itoa_fill(nbr, nb, len, sign));
}
