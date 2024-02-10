/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:45:07 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/06 21:49:09 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_printf_iter(va_list args, const char *str)
{
	int			printed;
	t_format	format;
	int			tmp;

	printed = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			tmp = ft_printf_format(&str, &format, args);
			if (tmp == -1)
				return (-1);
			printed += tmp;
		}
		else
		{
			if (ft_putchar_fd_r(*str, 1) == -1)
				return (-1);
			printed++;
		}
		if (*str)
			str++;
	}
	return (printed);
}

int	ft_printf(const char *str, ...)
{
	va_list			args;
	int				printed;

	va_start (args, str);
	printed = ft_printf_iter(args, str);
	va_end(args);
	return (printed);
}
