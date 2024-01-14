/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:50:48 by ybouchma          #+#    #+#             */
/*   Updated: 2023/11/15 09:00:02 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_flags(char c, va_list ptr);

int	ft_printf(const char *format, ...)
{
	size_t	i;
	int		len;
	va_list	ptr;

	if (!format)
		return (-1);
	len = 0;
	i = 0;
	va_start(ptr, format);
	while (format[i])
	{
		if (format[i] == '%')
			len += check_flags(format[++i], ptr);
		else
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(ptr);
	return (len);
}

int	check_flags(char c, va_list ptr)
{
	int	len;

	len = 0;
	if (c == '%')
		len += write(1, "%", 1);
	else if (c == 'c')
		len += print_char(va_arg(ptr, int));
	else if (c == 's')
		len += print_str(va_arg(ptr, char *));
	else if (c == 'p')
		len += print_addr(va_arg(ptr, void *));
	else if (c == 'd' || c == 'i')
		len += print_int(va_arg(ptr, int));
	else if (c == 'u')
		len += print_uint(va_arg(ptr, unsigned int));
	else if (c == 'x' || c == 'X')
		len += print_hex(va_arg(ptr, int), c);
	else
	{
		len += print_char('%');
		len += print_char(c);
	}
	return (len);
}
