#include "libft/libft.h"
#include "so_long_bonus.h"

void	player_killed(t_so_long *ptr)
{
	ft_printf("noob\n");
	destroy_all(*ptr);
}

void	go_up(t_so_long *ptr)
{
	int	pp[2];
	int	y;
	int	x;

	get_player_position(pp, ptr->map_2d);
	y = pp[0];
	x = pp[1];
	if (ptr->map_2d[y - 1][x] == 'X')
		player_killed(ptr);
	if (ptr->map_2d[y - 1][x] == '1' || \
			(ptr->map_2d[y - 1][x] == 'E' && ptr->exit))
		return ;
	if (ptr->map_2d[y - 1][x] == 'C')
		ptr->available_coins -= 1 ;
	ptr->map_2d[y - 1][x] = 'P';
	ptr->map_2d[y][x] = '0';
	mlx_put_image_to_window(ptr->mlx, \
			ptr->mlx_win, ptr->assets.floor, x * 32, y * 32);
	mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, \
			ptr->assets.player.back, x * 32, (y - 1) * 32);
	ptr->counter++;
	ptr->last_pp = 1;
}

void	go_down(t_so_long *ptr)
{
	int	pp[2];
	int	y;
	int	x;

	get_player_position(pp, ptr->map_2d);
	y = pp[0];
	x = pp[1];
	if (ptr->map_2d[y + 1][x] == 'X')
		player_killed(ptr);
	if (ptr->map_2d[y + 1][x] == '1' || \
			(ptr->map_2d[y + 1][x] == 'E' && ptr->exit))
		return ;
	if (ptr->map_2d[y + 1][x] == 'C')
		ptr->available_coins -= 1 ;
	ptr->map_2d[y + 1][x] = 'P';
	ptr->map_2d[y][x] = '0';
	mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, \
			ptr->assets.floor, x * 32, y * 32);
	mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, \
			ptr->assets.player.front, x * 32, (y + 1) * 32);
	ptr->counter++;
	ptr->last_pp = 3;
}

void	go_left(t_so_long *ptr)
{
	int	pp[2];
	int	y;
	int	x;

	get_player_position(pp, ptr->map_2d);
	y = pp[0];
	x = pp[1];
	if (ptr->map_2d[y][x + 1] == 'X')
		player_killed(ptr);
	if (ptr->map_2d[y][x + 1] == '1' || \
			(ptr->map_2d[y][x + 1] == 'E' && ptr->exit))
		return ;
	if (ptr->map_2d[y][x + 1] == 'C')
		ptr->available_coins -= 1 ;
	ptr->map_2d[y][x + 1] = 'P';
	ptr->map_2d[y][x] = '0';
	mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.floor, x * 32, y * 32);
	mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, \
			ptr->assets.player.right, (x + 1) * 32, y * 32);
	ptr->counter++;
	ptr->last_pp = 2;
}

void	go_rigth(t_so_long *ptr)
{
	int	pp[2];
	int	y;
	int	x;

	get_player_position(pp, ptr->map_2d);
	y = pp[0];
	x = pp[1];
	if (ptr->map_2d[y][x - 1] == 'X')
		player_killed(ptr);
	if (ptr->map_2d[y][x - 1] == '1' || \
			(ptr->map_2d[y][x - 1] == 'E' && ptr->exit))
		return ;
	if (ptr->map_2d[y][x - 1] == 'C')
		ptr->available_coins -= 1 ;
	ptr->map_2d[y][x - 1] = 'P';
	ptr->map_2d[y][x] = '0';
	mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, \
			ptr->assets.floor, x * 32, y * 32);
	mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, \
			ptr->assets.player.left, (x - 1) * 32, y * 32);
	ptr->counter++;
	ptr->last_pp = 4;
}


