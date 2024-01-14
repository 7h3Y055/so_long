/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:51:26 by ybouchma          #+#    #+#             */
/*   Updated: 2023/11/24 15:22:35 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_int(int n)
{
	static int	len;
	int			a;

	a = 0;
	len = 0;
	if (n == -2147483648)
	{
		len += print_str("-2147483648");
		return (len);
	}
	if (n < 0)
	{
		n *= -1;
		a += print_char('-');
	}
	if (n > 9)
		print_int(n / 10);
	len += print_char(n % 10 + 48);
	return (len + a);
}
