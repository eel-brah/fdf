/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print_ints_format_helpers.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:10:01 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/14 14:29:45 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_printf_get_print_pres(t_format format, int i,
								int *precision, char **pres)
{
	int	print;

	print = ft_printf_get_print(format, i, precision);
	return (print + ft_printf_get_pres(format, i, pres));
}

int	ft_printf_print_format_helper(t_format format, int *print,
									int i, char *pres)
{
	int	tmp;

	if (format.flags & 1)
		tmp = ft_printf_print_format_zero(format, print, i, pres);
	else if (format.nmb > *print && format.nmb > *print)
		tmp = ft_printf_print_format_nmb(format, print, i, pres);
	else
		tmp = ft_printf_print_s1(format, pres, i);
	return (tmp);
}

int	ft_printf_get_pres(t_format format, int i, char **pres)
{
	int	print;

	print = 0;
	if (format.specifier == 'i' || format.specifier == 'd')
	{
		if (format.flags & 1 << 3 && i >= 0)
			*pres = "+";
		else if (format.flags & 1 << 4 && i >= 0)
			*pres = " ";
		else if (i < 0)
			*pres = "-";
		if (*pres)
			print++;
	}
	else if ((format.specifier == 'x' || format.specifier == 'X')
		&& i != 0 && format.flags & 1 << 5)
	{
		if (format.specifier == 'x')
			*pres = "0x";
		else
			*pres = "0X";
		print += 2;
	}
	return (print);
}

int	ft_int_len(int n, char c)
{
	unsigned int	nb;
	int				len;

	len = 0;
	if (n == 0)
		return (1);
	nb = n;
	if (c != 'u' && n < 0)
		nb *= -1;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}
