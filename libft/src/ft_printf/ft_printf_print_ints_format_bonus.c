/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_ints_format.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:06:16 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/14 14:12:46 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_printf_pirnt_ints_format(int i, t_format format)
{
	int		print;
	char	*pres;
	int		precision;
	int		tmp;

	precision = 0;
	pres = NULL;
	print = ft_printf_get_print_pres(format, i, &precision, &pres);
	if ((format.flags & 1 << 2))
	{
		if (ft_printf_print_s3(format, pres, i) == -1)
			return (-1);
		tmp = ft_printf_print_format_hyphen(format, i, precision, &print);
	}
	else if (format.flags & 1 << 6)
	{
		if (ft_pirntf_padding_s1(format, &print) == -1)
			return (-1);
		tmp = ft_printf_print_format_prcs(format, i, precision, pres);
	}
	else
		tmp = ft_printf_print_format_helper(format, &print, i, pres);
	if (tmp == -1)
		return (-1);
	return (print);
}

int	ft_printf_print_format_hyphen(t_format format, int i,
									int precision, int *print)
{
	int	padding;

	padding = ft_printf_get_padding(format.hyphen_nmb, *print);
	if (ft_printf_print_paddings(precision, '0') == -1)
		return (-1);
	if (ft_printf_print_s2(format, i) == -1)
		return (-1);
	if (ft_printf_print_paddings(padding, ' ') == -1)
		return (-1);
	*print += padding;
	return (0);
}

int	ft_printf_print_format_prcs(t_format format, int i,
								int precision, char *pres)
{
	if (ft_printf_print_s3(format, pres, i) == -1)
		return (-1);
	if (ft_printf_print_paddings(precision, '0') == -1)
		return (-1);
	if (ft_printf_print_s2(format, i) == -1)
		return (-1);
	return (0);
}

int	ft_printf_print_format_zero(t_format format, int *print, int i, char *pres)
{
	int	padding;

	padding = ft_printf_get_padding(format.zero_nmb, *print);
	*print += padding;
	if (ft_printf_print_s3(format, pres, i) == -1)
		return (-1);
	if (ft_printf_print_paddings(padding, '0') == -1)
		return (-1);
	if (ft_printf_print_s2(format, i) == -1)
		return (-1);
	return (0);
}

int	ft_printf_print_format_nmb(t_format format, int *print, int i, char *pres)
{
	int	padding;

	padding = ft_printf_get_padding(format.nmb, *print);
	*print += padding;
	if (ft_printf_print_paddings(padding, ' ') == -1)
		return (-1);
	if (ft_printf_print_s1(format, pres, i) == -1)
		return (-1);
	return (0);
}
