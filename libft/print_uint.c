/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:51:39 by ybouchma          #+#    #+#             */
/*   Updated: 2023/11/24 15:05:12 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_uint(unsigned int n)
{
	static int	len;

	len = 0;
	if (n > 9)
		print_uint(n / 10);
	len += print_char(n % 10 + 48);
	return (len);
}
