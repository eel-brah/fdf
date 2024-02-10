/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_ints_adrs_helpers.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:28:49 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/14 14:29:17 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_printf_get_padding(int nmb, int print)
{
	int	padding;

	padding = nmb;
	if (padding > print)
		return (padding - print);
	else
		return (0);
}

int	ft_printf_print_paddings(int pad, char c)
{
	while (pad > 0)
	{
		if (ft_putchar_fd_r(c, 1) == -1)
			return (-1);
		pad--;
	}
	return (0);
}

int	ft_hex_len(unsigned long p)
{
	int	len;

	len = 0;
	if (p == 0)
		return (1);
	while (p > 0)
	{
		p /= 16;
		len++;
	}
	return (len);
}

int	ft_printf_get_print(t_format format, unsigned long i, int *precision)
{
	int	print;

	print = 0;
	if (format.specifier == 'x' || format.specifier == 'X')
		print = ft_hex_len((unsigned int)i);
	else if (format.specifier == 'p')
		print = ft_hex_len(i);
	else
		print = ft_int_len((int)i, format.specifier);
	if (i == 0 && format.flags & 1 << 6 && format.precision == 0)
		print = 0;
	if (format.specifier == 'p')
	{
		print += 2;
		if (format.precision > print)
			*precision = format.precision - print + 2;
	}
	else
		if (format.precision > print)
			*precision = format.precision - print;
	return (print + *precision);
}

int	ft_pirntf_padding_s1(t_format format, int *print)
{
	int	padding;

	padding = 0;
	if (format.zero_nmb > *print || format.nmb > *print)
	{
		if (!(format.flags & 1 << 2))
		{
			if (format.zero_nmb > format.nmb)
				padding = format.zero_nmb - *print;
			else
				padding = format.nmb - *print;
			*print += padding;
			if (ft_printf_print_paddings(padding, ' ') == -1)
				return (-1);
		}
	}
	return (0);
}
