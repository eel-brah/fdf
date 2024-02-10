/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:12:32 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/02 15:24:24 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void	ft_putnbr(unsigned int nb, int fd)
{
	if (nb < 10)
	{
		ft_putchar_fd (nb + 48, fd);
		return ;
	}
	ft_putnbr (nb / 10, fd);
	ft_putchar_fd (nb % 10 + 48, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (fd < 0)
		return ;
	nb = n;
	if (n < 0)
	{
		nb *= -1;
		ft_putchar_fd('-', fd);
	}
	ft_putnbr(nb, fd);
}
