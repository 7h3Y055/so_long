/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:58:46 by ybouchma          #+#    #+#             */
/*   Updated: 2023/10/30 17:58:47 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;

	i = 0;
	if (!ft_strlen(to_find))
		return ((char *)str);
	if (!len)
		return (NULL);
	while (str[i] && i + ft_strlen(to_find) <= len)
	{
		if (ft_strncmp(&str[i], to_find, ft_strlen(to_find)) == 0)
			return ((char *) &str[i]);
		i++;
	}
	return (NULL);
}
