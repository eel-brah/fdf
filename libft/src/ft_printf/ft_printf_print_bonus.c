/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:51:14 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/16 15:17:01 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_format_check(t_format format)
{
	if (format.flags & 1 << 6)
	{
		if (format.precision == -1)
			return (-1);
	}
	else if (format.flags & 1 << 2)
	{
		if (format.hyphen_nmb == -1)
			return (-1);
	}
	else if (format.flags & 1)
	{
		if (format.zero_nmb == -1)
			return (-1);
	}
	else if (format.nmb == -1)
		return (-1);
	return (0);
}

int	ft_printf_print_chars_formats(va_list args, t_format format)
{
	int		print;
	char	c;
	char	*str;
	int		tmp;

	c = 0;
	str = NULL;
	print = 0;
	print = ft_printf_print_chars_helper(format, args, &str, &c);
	if (format.flags & 1 << 2)
		tmp = ft_printf_print_char_hyphen(format, &print, str, c);
	else if (format.flags & 1)
		tmp = ft_printf_print_char_zero(format, &print, str, c);
	else if (format.nmb && format.nmb > print)
		tmp = ft_printf_print_char_nmb(format, &print, str, c);
	else
		tmp = ft_printf_print_putchars(format.specifier, print, str, c);
	if (tmp == -1)
		return (-1);
	return (print);
}

int	ft_printf_print_adrs_format(va_list args, t_format format)
{
	unsigned long	p;
	int				precision;
	int				print;
	int				tmp;

	p = (unsigned long)va_arg(args, void *);
	precision = 0;
	print = ft_printf_get_print(format, p, &precision);
	if ((format.flags & 1 << 2
			&& (precision == 0 || format.hyphen_nmb > print - precision)))
		tmp = ft_printf_adrs_print_hyphen(format, p, &print, precision);
	else if (format.flags & 1 << 6)
		tmp = ft_printf_adrs_print_precision(format, p, &print, precision);
	else if (format.flags & 1)
		tmp = ft_printf_adrs_print_zero(format, p, &print);
	else if (format.nmb > print && format.nmb > print)
		tmp = ft_printf_adrs_print_nmb(format, p, &print);
	else
		tmp = ft_printf_adrs_print_non(format, p);
	if (tmp == -1)
		return (-1);
	return (print);
}

int	ft_printf_ints(va_list args, t_format format)
{
	int	i;

	i = va_arg(args, int);
	return (ft_printf_pirnt_ints_format(i, format));
}
