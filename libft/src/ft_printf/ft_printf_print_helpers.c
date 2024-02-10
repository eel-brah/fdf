/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:49:07 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/14 15:35:35 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_putchar_fd_r(char c, int fd)
{
	return (write (fd, &c, 1));
}

int	ft_puthex(unsigned long p, char *hex)
{
	if (p < 16)
		return (ft_putchar_fd_r(hex[p], 1));
	if (ft_puthex(p / 16, hex) == -1)
		return (-1);
	return (ft_putchar_fd_r(hex[p % 16], 1));
}

int	ft_putnbr_r(unsigned int nb, int fd)
{
	if (nb < 10)
		return (ft_putchar_fd_r (nb + 48, fd));
	if (ft_putnbr_r (nb / 10, fd) == -1)
		return (-1);
	return (ft_putchar_fd_r (nb % 10 + 48, fd));
}

int	ft_putnbr_fd_r(int n, char c, int fd)
{
	unsigned int	nb;

	nb = n;
	if (c != 'u' && n < 0)
		nb *= -1;
	return (ft_putnbr_r(nb, fd));
}

int	ft_putstr_fd_r(char *str, int fd, int len)
{
	if (!str)
	{
		if (len > 6)
			len = 6;
		if (write(fd, "(null)", len) == -1)
			return (-1);
	}
	else if (*str)
	{
		if (write(fd, str, len) == -1)
			return (-1);
	}
	return (1);
}
