#include "so_long_bonus.h"

char	*read_and_check_map(int fd)
{
	char	*map;
	char	*tmp;
	char	**map_2d;

	tmp = read_map(fd);
	if (tmp[ft_strlen(tmp) - 1] != '\n')
	{
		map = ft_strjoin(tmp, "\n");
		free(tmp);
	}
	else
		map = tmp;
	create_2d_map(map, &map_2d);
	if (check_components(map))
		return (free_map(map_2d), \
			ft_putendl_fd("[!MAP] Contain invalid component", 2), NULL);
	if (check_rectangular(map_2d))
		return (free(map), free_map(map_2d), \
			ft_putendl_fd("[!MAP] Not rectangular", 2), NULL);
	if (check_closed(map_2d))
		return (free(map), free_map(map_2d), \
			ft_putendl_fd("[!MAP] Not closed by wall", 2), NULL);
	if (check_valid_path(map))
		return (free_map(map_2d), ft_putendl_fd("[!MAP] Invalid path", 2), NULL);
	if (check_coins(map, map_2d))
		return (free_map(map_2d), ft_putendl_fd("[!MAP] Player can't collet all coins", 2), NULL);
	return (free_map(map_2d), map);
}

int	check_coins(char *map, char **map_2d)
{
	t_so_long ptr;
	int	y;
	int	x;
	int	c;

	c = 0;
	y = 0;
	while (map_2d[y])
	{
		x = 0;
		while (map_2d[y][x])
		{
			if (map_2d[y][x] == 'C')
				c++;
			x++;
		}
		y++;
	}
	ptr.map_2d = map_2d;
	ptr.map = map;
	if (c != count_available_coins(&ptr))
		return (free(map), 1);
	return (0);
}

char	*read_map(int fd)
{
	char	*map;
	char	*tmp;
	char	*tmp2;

	map = (char *)ft_calloc(1, 1);
	tmp = NULL;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		tmp2 = ft_strjoin(map, tmp);
		free(tmp);
		free(map);
		map = tmp2;
	}
	return (map);
}

int	create_2d_map(char *map, char ***map_2d)
{
	int	i;
	int	j;
	int	u;

	map_2d[0] = malloc(sizeof(char *) * (map_y_len(map) + 2));
	if (!map_2d[0])
		return (free(map), 1);
	i = 0;
	j = 0;
	map_2d[0][0] = malloc(sizeof(char) * (map_x_len(map) + 1));
	while (map[j] && map[j] != '\n')
		map_2d[0][0][j++] = '1';
	map_2d[0][0][j] = '\0';
	u = 1;
	while (map[i])
	{
		map_2d[0][u] = malloc(sizeof(char) * (map_x_len(map) + 1));
		j = 0;
		while (map[i] && !(map[i] == '\n' || map[i] == '\r'))
			map_2d[0][u][j++] = map[i++];
		map_2d[0][u][j] = 0;
		u++;
		i++;
	}
	map_2d[0][u] = NULL;
	return (0);
}

int	check_components(char *map)
{
	int				i;
	t_components	*content;

	i = 0;
	content = ft_calloc(sizeof(t_components), 1);
	while (map[i])
	{
		if (map[i] == '1')
			content->one++;
		else if (map[i] == '0')
			content->zero++;
		else if (map[i] == 'E')
			content->e++;
		else if (map[i] == 'C')
			content->c++;
		else if (map[i] == 'P')
			content->p++;
		else if (map[i] == 'X')
			content->x++;
		else if (!(map[i] == '\n' || map[i] == '\r'))
			content->others++;
		i++;
	}
	if (content->others || !content->c || content->e != 1 || content->p != 1)
		return (free(map), free(content), 1);
	return (free(content), 0);
}

int	check_rectangular(char **map_2d)
{
	int		i;

	i = 1;
	while (map_2d[i])
	{
		if (ft_strlen(map_2d[i - 1]) != ft_strlen(map_2d[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_closed(char **map_2d)
{
	int		i;
	int		y;

	y = 0;
	while (map_2d[y])
		y++;
	i = -1;
	while (map_2d[1][++i])
		if (map_2d[1][i] != '1' || map_2d[y - 1][i] != '1')
			return (1);
	i = 0;
	while (map_2d[i] && map_2d[i][0])
	{
		if (map_2d[i][0] != '1' || map_2d[i][ft_strlen(map_2d[0]) - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_path(char *map)
{
	char	**map_2d;
	int		player_position[2];

	if (create_2d_map(map, &map_2d))
		return (1);
	get_player_position(player_position, map_2d);
	if (!valid_path(map_2d, player_position[0], player_position[1]))
		return (free_map(map_2d), free(map), 1);
	free_map(map_2d);
	return (0);
}







