/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_generator_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:40:43 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/16 22:12:45 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

void	ft_format_initialization(t_format *format, char *formats)
{
	format->flags = 0;
	format->nmb = 0;
	format->specifier = formats[ft_strlen(formats)-1];
	format->precision = 0;
	format->hyphen_nmb = 0;
	format->zero_nmb = 0;
}

void	ft_format_iter_re(t_format *format, char *formats)
{
	int	i;

	ft_get_zero_flag_nmb (formats, format);
	i = ft_atoi_strict (formats + 1);
	if (i != 0)
		format->hyphen_nmb = i;
}

void	ft_format_iter(char c, t_format *format, char *formats)
{
	if (c == '-')
		ft_format_hyphen(format, formats + 1);
	else if (c == '+')
	{
		format->flags = format->flags | 1 << 3;
		ft_format_iter_re(format, formats);
	}
	else if (c == ' ')
	{
		format->flags = format->flags | 1 << 4;
		ft_format_iter_re(format, formats);
	}
	else if (c == '#')
	{
		format->flags = format->flags | 1 << 5;
		ft_format_iter_re(format, formats);
	}
	else if (c == '.')
	{
		format->flags = format->flags | 1 << 6;
		format->precision = ft_atoi_strict (formats + 1);
	}
}

t_format	ft_format_genarator(char *formats)
{
	char		*ptr;
	char		*format_set;
	int			index;
	t_format	format;

	index = 0;
	format_set = "-+ #.";
	ft_format_initialization(&format, formats);
	ft_get_zero_flag_nmb(formats, &format);
	while (*(formats + index))
	{
		ptr = ft_strchr(format_set, *(formats + index));
		if (ptr)
			ft_format_iter(*ptr, &format, formats + index);
		index++;
	}
	return (format);
}

int	ft_printf_format(const char **str, t_format *format, va_list args)
{
	char	*formats;
	int		printed;

	printed = 0;
	if (!*str)
		return (0);
	formats = ft_get_format(*str);
	if (formats == (void *)-1)
		return (-1);
	else if (!formats)
	{
		*str = ft_format_skep((char *)*str);
		return (0);
	}
	*format = ft_format_genarator(formats);
	if (ft_format_check(*format) == -1)
		return (-1);
	printed = ft_printf_formating(args, *format);
	*str += ft_strlen(formats) - 1;
	free(formats);
	if (printed == -1)
		return (-1);
	return (printed);
}
