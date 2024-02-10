/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_adrs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:21:01 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/14 14:24:31 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_printf_adrs_print_hyphen(t_format format,
								unsigned long p, int *print, int precision)
{
	int		padding;
	char	*hex;

	hex = "0123456789abcdef";
	padding = ft_printf_get_padding(format.hyphen_nmb, *print);
	*print += padding;
	if (ft_putstr_fd_r("0x", 1, 2) == -1)
		return (-1);
	if (ft_printf_print_paddings(precision, '0') == -1)
		return (-1);
	if (!(p == 0 && format.flags & 1 << 6 && format.precision == 0))
		if (ft_puthex(p, hex) == -1)
			return (-1);
	if (ft_printf_print_paddings(padding, ' ') == -1)
		return (-1);
	return (0);
}

int	ft_printf_adrs_print_precision(t_format format,
									unsigned long p, int *print, int precision)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (ft_pirntf_padding_s1(format, print) == -1)
		return (-1);
	if (ft_putstr_fd_r("0x", 1, 2) == -1)
		return (-1);
	if (ft_printf_print_paddings(precision, '0') == -1)
		return (-1);
	if (!(p == 0 && format.flags & 1 << 6 && format.precision == 0))
		if (ft_puthex(p, hex) == -1)
			return (-1);
	return (0);
}

int	ft_printf_adrs_print_zero(t_format format, unsigned long p, int *print)
{
	int		padding;
	char	*hex;

	hex = "0123456789abcdef";
	padding = ft_printf_get_padding(format.zero_nmb, *print);
	*print += padding;
	if (ft_putstr_fd_r("0x", 1, 2) == -1)
		return (-1);
	if (ft_printf_print_paddings(padding, '0') == -1)
		return (-1);
	if (!(p == 0 && format.flags & 1 << 6 && format.precision == 0))
		if (ft_puthex(p, hex) == -1)
			return (-1);
	return (0);
}

int	ft_printf_adrs_print_nmb(t_format format, unsigned long p, int *print)
{
	int		padding;
	char	*hex;

	hex = "0123456789abcdef";
	padding = ft_printf_get_padding(format.nmb, *print);
	*print += padding;
	if (ft_printf_print_paddings(padding, ' ') == -1)
		return (-1);
	if (ft_putstr_fd_r("0x", 1, 2) == -1)
		return (-1);
	if (!(p == 0 && format.flags & 1 << 6 && format.precision == 0))
		if (ft_puthex(p, hex) == -1)
			return (-1);
	return (0);
}

int	ft_printf_adrs_print_non(t_format format, unsigned long p)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (ft_putstr_fd_r("0x", 1, 2) == -1)
		return (-1);
	if (!(p == 0 && format.flags & 1 << 6 && format.precision == 0))
		if (ft_puthex(p, hex) == -1)
			return (-1);
	return (0);
}
