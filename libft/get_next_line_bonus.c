/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:16:13 by ybouchma          #+#    #+#             */
/*   Updated: 2023/11/24 12:12:35 by ybouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line_bonus(int fd)
{
	static char	*list[1024];
	char		*next_line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	list[fd] = read_data(fd, list[fd]);
	if (!list[fd])
		return (NULL);
	if (ft_strlen(list[fd]) == 0)
	{
		free(list[fd]);
		list[fd] = NULL;
		return (NULL);
	}
	next_line = get_nline(list[fd]);
	list[fd] = clean(list[fd]);
	return (next_line);
}
