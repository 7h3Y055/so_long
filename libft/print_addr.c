/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_addr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:51:05 by ybouchma          #+#    #+#             */
/*   Updated: 2023/11/24 15:21:32 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_addr_helper(unsigned char *c);

int	print_addr(void *ptr)
{
	int				len;
	unsigned char	*c;

	if (!ptr)
	{
		print_str("(nil)");
		return (5);
	}
	c = (unsigned char *)&ptr;
	len = print_addr_helper(c);
	return (len);
}

int	print_addr_helper(unsigned char *c)
{
	int	len;
	int	i;
	int	a;

	len = print_str("0x");
	i = 7;
	a = 0;
	while (i >= 0)
	{
		if (c[i])
		{
			len += print_hex(c[i], 'x');
			a = 1;
		}
		else if (a)
			len += print_str("00");
		i--;
	}
	return (len);
}
