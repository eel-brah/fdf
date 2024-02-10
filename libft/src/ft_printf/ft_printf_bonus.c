/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 21:45:09 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/16 22:13:31 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

char	*ft_format_skep(char *str)
{
	char	*ptr;
	char	*flags;
	int		i;

	i = 0;
	flags = "-0.# +123456789";
	ptr = flags;
	while (*(str + i) && ptr)
		ptr = ft_strchr(flags, *(str + i++));
	return (str + i);
}

int	ft_atoi_strict(const char *str)
{
	int		nb;
	int		nbr;

	nb = 0;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nb * 10 + (*str++ - '0');
		if (nb > nbr || nbr == 2147483647)
			return (-1);
		nb = nbr;
	}
	return (nb);
}

int	ft_printf_formating(va_list args, t_format format)
{
	int	tmp;

	tmp = 0;
	if (format.specifier == 'c')
		tmp = ft_printf_print_chars_formats(args, format);
	else if (format.specifier == 's')
		tmp = ft_printf_print_chars_formats(args, format);
	else if (format.specifier == 'p')
		tmp = ft_printf_print_adrs_format(args, format);
	else if (format.specifier == 'd' || format.specifier == 'i')
		tmp = ft_printf_ints(args, format);
	else if (format.specifier == 'u')
		tmp = ft_printf_ints(args, format);
	else if (format.specifier == 'x' || format.specifier == 'X')
		tmp = ft_printf_ints(args, format);
	else if (format.specifier)
		tmp = ft_printf_print_chars_formats(args, format);
	return (tmp);
}

char	*ft_get_format(const char *str)
{
	char	*ptr;
	char	*flags;
	int		i;

	i = 0;
	flags = "-0.# +123456789";
	ptr = flags;
	while (*(str + i) && ptr)
		ptr = ft_strchr(flags, *(str + i++));
	if (!ptr && i > 0)
	{
		ptr = ft_substr(str, 0, i);
		if (!ptr)
			return ((void *)-1);
		return (ptr);
	}
	else
		return (NULL);
}
