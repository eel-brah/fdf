/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_chars.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:59:02 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/14 13:59:21 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_printf_print_putchars(char x, int print, char *str, char c)
{
	if (x == 's')
	{
		if (ft_putstr_fd_r(str, 1, print) == -1)
			return (-1);
	}
	else
	{
		if (ft_putchar_fd_r(c, 1) == -1)
			return (-1);
	}
	return (0);
}

int	ft_printf_print_char_hyphen(t_format format, int *print, char *str, char c)
{
	int	padding;

	if (ft_printf_print_putchars(format.specifier, *print, str, c) == -1)
		return (-1);
	padding = ft_printf_get_padding(format.hyphen_nmb, *print);
	*print += padding;
	if (ft_printf_print_paddings(padding, ' ') == -1)
		return (-1);
	return (0);
}

int	ft_printf_print_char_zero(t_format format, int *print, char *str, char c)
{
	int	padding;

	padding = ft_printf_get_padding(format.zero_nmb, *print);
	if (ft_printf_print_paddings(padding, '0') == -1)
		return (-1);
	if (ft_printf_print_putchars(format.specifier, *print, str, c) == -1)
		return (-1);
	*print += padding;
	return (0);
}

int	ft_printf_print_char_nmb(t_format format, int *print, char *str, char c)
{
	int	padding;

	padding = ft_printf_get_padding(format.nmb, *print);
	if (ft_printf_print_paddings(padding, ' ') == -1)
		return (-1);
	if (ft_printf_print_putchars(format.specifier, *print, str, c) == -1)
		return (-1);
	*print += padding;
	return (0);
}

int	ft_printf_print_chars_helper(t_format format,
								va_list args, char **str, char *c)
{
	int	print;

	if (format.specifier == 's')
	{
		*str = va_arg(args, char *);
		if (*str)
			print = ft_strlen(*str);
		else
			print = 6;
	}
	else if (format.specifier == 'c')
	{
		*c = va_arg(args, int);
		print = 1;
	}
	else
	{
		*c = format.specifier;
		print = 1;
	}
	if (format.specifier == 's' && format.flags & 1 << 6)
		if (format.precision < print)
			print = format.precision;
	return (print);
}
