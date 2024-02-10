/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_fill_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:43:15 by eel-brah          #+#    #+#             */
/*   Updated: 2023/11/16 15:22:09 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_to_skip(char *formats)
{
	char	*ptr;
	int		skp;
	char	*to_skep;

	to_skep = "+ #";
	ptr = to_skep;
	skp = 0;
	while (ptr && *(formats + skp))
		ptr = ft_strchr(to_skep, *(formats + skp++));
	if (skp)
		skp--;
	return (skp);
}

int	ft_to_skip_digit(char *formats)
{
	char	*ptr;
	int		skp;
	char	*to_skep;

	to_skep = "0123456789";
	ptr = to_skep;
	skp = 0;
	while (ptr && *(formats + skp))
		ptr = ft_strchr(to_skep, *(formats + skp++));
	if (skp)
		skp--;
	return (skp);
}

void	ft_get_zero_flag_nmb_helper(char *tmp, t_format *format)
{
	int	skp;

	skp = ft_to_skip(tmp);
	if (ft_isdigit(*(tmp + skp)))
		format->zero_nmb = ft_atoi_strict(tmp + skp);
	else if (format->zero_nmb == 0)
		format->zero_nmb = format->nmb;
	tmp += skp;
	tmp += ft_to_skip_digit(tmp);
	skp = ft_to_skip(tmp);
	while (skp > 0)
	{
		if (ft_isdigit(*(tmp + skp)) && *(tmp + skp) != 48)
			format->zero_nmb = ft_atoi_strict(tmp + skp);
		tmp += skp;
		tmp += ft_to_skip_digit(tmp);
		skp = ft_to_skip(tmp);
	}
}

void	ft_get_zero_flag_nmb(char *formats, t_format *format)
{
	int		skp;
	char	*tmp;

	skp = ft_to_skip(formats);
	if (*(formats + skp) == '0')
	{
		format->flags = format->flags | 1;
		tmp = formats + skp + 1;
		ft_get_zero_flag_nmb_helper (tmp, format);
		if (format->zero_nmb != 0)
			format->hyphen_nmb = format->zero_nmb;
	}
	else if (ft_isdigit(*(formats + skp)))
	{
		format->nmb = ft_atoi_strict(formats + skp);
		if (format->nmb != 0)
		{
			format->hyphen_nmb = format->nmb;
			format->zero_nmb = format->nmb;
		}
	}
}

void	ft_format_hyphen(t_format *format, char *tmp)
{
	int	nmb;
	int	skp;

	nmb = 0;
	format->flags = format->flags | 1 << 2;
	nmb = ft_atoi_strict(tmp);
	if (nmb > 0 || nmb == -1)
		format->hyphen_nmb = nmb;
	tmp += ft_to_skip_digit(tmp);
	skp = ft_to_skip(tmp);
	while (skp > 0)
	{
		if (ft_isdigit(*(tmp + skp)) && *(tmp + skp) != 48)
			format->hyphen_nmb = ft_atoi_strict(tmp + skp);
		tmp += skp;
		tmp += ft_to_skip_digit(tmp);
		skp = ft_to_skip(tmp);
	}
}
