/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:51:21 by ybouchma          #+#    #+#             */
/*   Updated: 2023/11/24 15:05:33 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_hex(unsigned int n, char c)
{
	char		*hex_l;
	char		*hex_u;
	static int	len;

	hex_l = "0123456789abcdef";
	hex_u = "0123456789ABCDEF";
	len = 0;
	if (n > 15)
		print_hex(n / 16, c);
	if (c == 'x')
		len += print_char(hex_l[n % 16]);
	else
		len += print_char(hex_u[n % 16]);
	return (len);
}
