/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-brah <eel-brah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:32:31 by eel-brah          #+#    #+#             */
/*   Updated: 2023/12/15 18:23:07 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct s_format
{
	char	flags;
	int		nmb;
	int		hyphen_nmb;
	int		zero_nmb;
	int		precision;
	char	specifier;
}	t_format;

char		*ft_format_skep(char *str);
int			ft_atoi_strict(const char *str);
int			ft_printf_formating(va_list args, t_format format);
char		*ft_get_format(const char *str);
int			ft_to_skip(char *formats);
int			ft_format_check(t_format format);
int			ft_to_skip_digit(char *formats);
void		ft_get_zero_flag_nmb_helper(char *tmp, t_format *format);
void		ft_get_zero_flag_nmb(char *formats, t_format *format);
void		ft_format_hyphen(t_format *format, char *tmp);
void		ft_format_initialization(t_format *format, char *formats);
void		ft_format_iter_re(t_format *format, char *formats);
void		ft_format_iter(char c, t_format *format, char *formats);
t_format	ft_format_genarator(char *formats);
int			ft_printf_format(const char **str, t_format *format, va_list args);
int			ft_printf_iter(va_list args, const char *str);
int			ft_printf(const char *str, ...);
int			ft_putchar_fd_r(char c, int fd);
int			ft_puthex(unsigned long p, char *hex);
int			ft_putnbr_r(unsigned int nb, int fd);
int			ft_putnbr_fd_r(int n, char c, int fd);
int			ft_putstr_fd_r(char *str, int fd, int len);
int			ft_printf_print_putchars(char x, int print, char *str, char c);
int			ft_printf_print_char_hyphen(t_format format,
				int *print, char *str, char c);
int			ft_printf_print_char_zero(t_format format,
				int *print, char *str, char c);
int			ft_printf_print_char_nmb(t_format format,
				int *print, char *str, char c);
int			ft_printf_print_chars_helper(t_format format,
				va_list args, char **str, char *c);
int			ft_printf_pirnt_ints_format(int i, t_format format);
int			ft_printf_print_format_hyphen(t_format format, int i,
				int precision, int *print);
int			ft_printf_print_format_prcs(t_format format, int i,
				int precision, char *pres);
int			ft_printf_print_format_zero(t_format format,
				int *print, int i, char *pres);
int			ft_printf_print_format_nmb(t_format format,
				int *print, int i, char *pres);
int			ft_printf_get_pres(t_format format, int i, char **pres);
int			ft_int_len(int n, char c);
int			ft_printf_print_format_helper(t_format format, int *print,
				int i, char *pres);
int			ft_printf_get_print_pres(t_format format, int i,
				int *precision, char **pres);
int			ft_printf_print_hex(t_format format, int i);
int			ft_printf_print_s2(t_format format, int i);
int			ft_printf_print_s3(t_format format, char *pres, int i);
int			ft_printf_print_s1(t_format format, char *pres, int i);
int			ft_printf_adrs_print_non(t_format format, unsigned long p);
int			ft_printf_adrs_print_nmb(t_format format,
				unsigned long p, int *print);
int			ft_printf_adrs_print_zero(t_format format,
				unsigned long p, int *print);
int			ft_printf_adrs_print_precision(t_format format,
				unsigned long p, int *print, int precision);
int			ft_printf_adrs_print_hyphen(t_format format,
				unsigned long p, int *print, int precision);
int			ft_printf_get_padding(int nmb, int print);
int			ft_printf_print_paddings(int pad, char c);
int			ft_hex_len(unsigned long p);
int			ft_printf_get_print(t_format format,
				unsigned long i, int *precision);
int			ft_pirntf_padding_s1(t_format format, int *print);
int			ft_printf_print_chars_formats(va_list args, t_format format);
int			ft_printf_print_adrs_format(va_list args, t_format format);
int			ft_printf_ints(va_list args, t_format format);

#endif