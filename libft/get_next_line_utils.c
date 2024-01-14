/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:16:01 by ybouchma          #+#    #+#             */
/*   Updated: 2023/11/24 15:21:53 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	read_data_helper(char **buffer, char *data)
{
	int	i;

	if (ft_strlen(*buffer) == 0)
	{
		free(*buffer);
		*buffer = NULL;
		return (0);
	}
	if (ft_strchr(*buffer, '\n'))
		return (1);
	i = 0;
	while (i < BUFFER_SIZE + 1)
		data[i++] = 0;
	return (0);
}
