/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_format_ints_format_helpers_        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:15:27 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/14 14:15:45 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_printf_print_hex(t_format format, int i)
{
	char	*hex_lower;
	char	*hex_upper;
	char	*hex;

	hex_lower = "0123456789abcdef";
	hex_upper = "0123456789ABCDEF";
	hex = hex_upper;
	if (format.specifier == 'x')
		hex = hex_lower;
	if (ft_puthex((unsigned int)i, hex) == -1)
		return (-1);
	return (0);
}

int	ft_printf_print_s2(t_format format, int i)
{
	if (!(i == 0 && format.flags & 1 << 6 && format.precision == 0))
	{
		if (format.specifier == 'x' || format.specifier == 'X')
		{
			if (ft_printf_print_hex(format, i) == -1)
				return (-1);
		}
		else
		{
			if (ft_putnbr_fd_r(i, format.specifier, 1) == -1)
				return (-1);
		}
	}
	return (0);
}

int	ft_printf_print_s3(t_format format, char *pres, int i)
{
	if (format.specifier == 'x' || format.specifier == 'X')
	{
		if (pres && i != 0 && ft_putstr_fd_r(pres, 1, ft_strlen(pres)) == -1)
			return (-1);
	}
	else
	{
		if (pres && ft_putchar_fd_r(*pres, 1) == -1)
			return (-1);
	}
	return (0);
}

int	ft_printf_print_s1(t_format format, char *pres, int i)
{
	if (ft_printf_print_s3(format, pres, i) == -1)
		return (-1);
	if (ft_printf_print_s2(format, i) == -1)
		return (-1);
	return (0);
}
