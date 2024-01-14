#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include "so_long_bonus.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <X11/keysym.h>

void	destroy_assets(t_so_long ptr)
{
	mlx_destroy_image(ptr.mlx, ptr.assets.coin.a);
	mlx_destroy_image(ptr.mlx, ptr.assets.coin.b);
	mlx_destroy_image(ptr.mlx, ptr.assets.coin.c);
	mlx_destroy_image(ptr.mlx, ptr.assets.coin.d);
	mlx_destroy_image(ptr.mlx, ptr.assets.coin.e);
	mlx_destroy_image(ptr.mlx, ptr.assets.coin.f);
	mlx_destroy_image(ptr.mlx, ptr.assets.coin.g);
	mlx_destroy_image(ptr.mlx, ptr.assets.coin.h);
	mlx_destroy_image(ptr.mlx, ptr.assets.door.close);
	mlx_destroy_image(ptr.mlx, ptr.assets.door.open);
	mlx_destroy_image(ptr.mlx, ptr.assets.enemy);
	mlx_destroy_image(ptr.mlx, ptr.assets.floor);
	mlx_destroy_image(ptr.mlx, ptr.assets.player.back);
	mlx_destroy_image(ptr.mlx, ptr.assets.player.front);
	mlx_destroy_image(ptr.mlx, ptr.assets.player.left);
	mlx_destroy_image(ptr.mlx, ptr.assets.player.right);
	mlx_destroy_image(ptr.mlx, ptr.assets.wall);
	mlx_destroy_image(ptr.mlx, ptr.assets.num.eight);
	mlx_destroy_image(ptr.mlx, ptr.assets.num.five);
	mlx_destroy_image(ptr.mlx, ptr.assets.num.foor);
	mlx_destroy_image(ptr.mlx, ptr.assets.num.nine);
	mlx_destroy_image(ptr.mlx, ptr.assets.num.one);
	mlx_destroy_image(ptr.mlx, ptr.assets.num.seven);
	mlx_destroy_image(ptr.mlx, ptr.assets.num.six);
	mlx_destroy_image(ptr.mlx, ptr.assets.num.three);
	mlx_destroy_image(ptr.mlx, ptr.assets.num.two);
	mlx_destroy_image(ptr.mlx, ptr.assets.num.zero);
	mlx_destroy_image(ptr.mlx, ptr.assets.black);
}

int	destroy_all(t_so_long *ptr)
{
	destroy_assets(*ptr);
	mlx_destroy_window(ptr->mlx, ptr->mlx_win);
	mlx_destroy_display(ptr->mlx);
	free(ptr->mlx);
	free(ptr->map);
	free_map(ptr->map_2d);
	exit(0);
}

void	get_exit_position(int *ep, t_so_long *ptr)
{
	ep[0] = 0;
	while (ep[0] < (int)map_y_len(ptr->map))
	{
		ep[1] = 0;
		while (ep[1] < (int)map_x_len(ptr->map))
		{
			if (ptr->map_2d[ep[0]][ep[1]] == 'E')
				return ;
			ep[1]++;
		}
		ep[0]++;
	}
}

void	enemy_animation_helper(t_so_long *ptr, int *ep)
{
	if (ptr->flag == 0)
	{
		if (ptr->map_2d[ep[0]][ep[1] + 1] == '0')
		{
			ptr->map_2d[ep[0]][ep[1] + 1] = 'X';
			mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.enemy, (ep[1] + 1) * 32, ep[0] * 32);
			ptr->map_2d[ep[0]][ep[1]] = '0';
			mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.floor, ep[1] * 32, ep[0] * 32);
		}
		else if (ptr->map_2d[ep[0]][ep[1] + 1] == 'P')
			player_killed(ptr);
	}
	else if (ptr->flag == 1)
	{
		if (ptr->map_2d[ep[0]][ep[1] - 1] == '0')
		{
			ptr->map_2d[ep[0]][ep[1] - 1] = 'X';
			mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.enemy, (ep[1] - 1) * 32, ep[0] * 32);
			ptr->map_2d[ep[0]][ep[1]] = '0';
			mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.floor, ep[1] * 32, ep[0] * 32);
		}
		else if (ptr->map_2d[ep[0]][ep[1] - 1] == 'P')
			player_killed(ptr);
	}
}

void	enemy_animation(t_so_long *ptr, int *enemy_speed)
{
	int			ep[2];
	static int x;

	*enemy_speed = 0;
	ep[0] = 0;
	while (ptr->map_2d[ep[0]])
	{
		ep[1] = 0;
		while (ptr->map_2d[ep[0]][ep[1]])
		{
			if (ptr->map_2d[ep[0]][ep[1]] == 'X')
			{
				enemy_animation_helper(ptr, ep);
				ep[1]++;
			}
			ep[1]++;
		}
		ep[0]++;
	}
	if (x == 0)
	{
		if (ptr->flag)
			ptr->flag = 0;
		else
			ptr->flag = 1;
		x = 1;
	}
	else
		x = 0;
}

int animations(t_so_long *ptr)
{
	static int	enemy_speed;
	static int	coin_speed;
	static int	rerendering;
	int			pp[2];

	usleep(20000);
	get_player_position(pp, ptr->map_2d);
	if (pp[0] == ptr->ep[0] && pp[1] == ptr->ep[1])
		destroy_all(ptr);
	if (ptr->available_coins == 0 && ptr->exit)
	{
		mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.door.open, ptr->ep[1] * 32, ptr->ep[0] * 32);
		ptr->exit = 0;
	}
	if (rerendering >= 100)
	{
		init_assets_in_window(ptr);
		counter(ptr);
	}
	if (enemy_speed >= ENEMY_SPEED)
		enemy_animation(ptr, &enemy_speed);
	if (coin_speed >= COIN_SPEED)
		coin_animition(ptr, &coin_speed);
	enemy_speed++;
	coin_speed++;
	rerendering++;
	return (0);
}

int	handle_input(int key, t_so_long *ptr)
{
	if (key == W)
		go_up(ptr);
	if (key == A)
		go_rigth(ptr);
	if (key == S)
		go_down(ptr);
	if (key == D)
		go_left(ptr);
	if (key == XK_Escape)
		destroy_all(ptr);
	return (0);
}

void	init_assets_player(t_so_long *ptr, int w)
{
	ptr->assets.player.back = mlx_xpm_file_to_image(ptr->mlx, "./textures/player/back.xpm", &w, &w);
	ptr->assets.player.front = mlx_xpm_file_to_image(ptr->mlx, "./textures/player/front.xpm", &w, &w);
	ptr->assets.player.left = mlx_xpm_file_to_image(ptr->mlx, "./textures/player/left.xpm", &w, &w);
	ptr->assets.player.right = mlx_xpm_file_to_image(ptr->mlx, "./textures/player/right.xpm", &w, &w);
}

void	init_assets_coin(t_so_long *ptr, int w)
{
	ptr->assets.coin.a = mlx_xpm_file_to_image(ptr->mlx, "./textures/coins/c1.xpm", &w, &w);
	ptr->assets.coin.b = mlx_xpm_file_to_image(ptr->mlx, "./textures/coins/c2.xpm", &w, &w);
	ptr->assets.coin.c = mlx_xpm_file_to_image(ptr->mlx, "./textures/coins/c3.xpm", &w, &w);
	ptr->assets.coin.d = mlx_xpm_file_to_image(ptr->mlx, "./textures/coins/c4.xpm", &w, &w);
	ptr->assets.coin.e = mlx_xpm_file_to_image(ptr->mlx, "./textures/coins/c5.xpm", &w, &w);
	ptr->assets.coin.f = mlx_xpm_file_to_image(ptr->mlx, "./textures/coins/c6.xpm", &w, &w);
	ptr->assets.coin.g = mlx_xpm_file_to_image(ptr->mlx, "./textures/coins/c7.xpm", &w, &w);
	ptr->assets.coin.h = mlx_xpm_file_to_image(ptr->mlx, "./textures/coins/c8.xpm", &w, &w);
}

void	init_assets_number(t_so_long *ptr, int w)
{
	ptr->assets.num.zero = mlx_xpm_file_to_image(ptr->mlx, "./textures/numbers/0.xpm", &w, &w);
	ptr->assets.num.one = mlx_xpm_file_to_image(ptr->mlx, "./textures/numbers/1.xpm", &w, &w);
	ptr->assets.num.two = mlx_xpm_file_to_image(ptr->mlx, "./textures/numbers/2.xpm", &w, &w);
	ptr->assets.num.three = mlx_xpm_file_to_image(ptr->mlx, "./textures/numbers/3.xpm", &w, &w);
	ptr->assets.num.foor = mlx_xpm_file_to_image(ptr->mlx, "./textures/numbers/4.xpm", &w, &w);
	ptr->assets.num.five = mlx_xpm_file_to_image(ptr->mlx, "./textures/numbers/5.xpm", &w, &w);
	ptr->assets.num.six = mlx_xpm_file_to_image(ptr->mlx, "./textures/numbers/6.xpm", &w, &w);
	ptr->assets.num.seven = mlx_xpm_file_to_image(ptr->mlx, "./textures/numbers/7.xpm", &w, &w);
	ptr->assets.num.eight = mlx_xpm_file_to_image(ptr->mlx, "./textures/numbers/8.xpm", &w, &w);
	ptr->assets.num.nine = mlx_xpm_file_to_image(ptr->mlx, "./textures/numbers/9.xpm", &w, &w);
}

void	init_assets(t_so_long *ptr)
{
	int w;
	
	w = 0;
	init_assets_player(ptr, w);
	init_assets_coin(ptr, w);
	init_assets_number(ptr, w);
	ptr->assets.door.close = mlx_xpm_file_to_image(ptr->mlx, "./textures/door/close.xpm", &w, &w);
	ptr->assets.door.open = mlx_xpm_file_to_image(ptr->mlx, "./textures/door/open.xpm", &w, &w);
	ptr->assets.enemy = mlx_xpm_file_to_image(ptr->mlx, "./textures/enemy.xpm", &w, &w);
	ptr->assets.wall = mlx_xpm_file_to_image(ptr->mlx, "./textures/wall.xpm", &w, &w);
	ptr->assets.floor = mlx_xpm_file_to_image(ptr->mlx, "./textures/floor.xpm", &w, &w);
	ptr->assets.black = mlx_xpm_file_to_image(ptr->mlx, "./textures/black.xpm", &w, &w);
}

void	*get_asset(t_so_long *ptr, char c)
{
	int n;

	n = 0;
	if (c == '1')
		return (ptr->assets.wall);
	if (c == '0')
		return (ptr->assets.floor);
	if (c == 'P')
	{
		if (ptr->last_pp == 1)
			return (ptr->assets.player.back);
		if (ptr->last_pp == 4)
			return (ptr->assets.player.left);
		if (ptr->last_pp == 3)
			return (ptr->assets.player.front);
		if (ptr->last_pp == 2)
			return (ptr->assets.player.right);
	}
	if (c == 'E')
	{
		if (ptr->exit)
			return (ptr->assets.door.close);
		else
			return (ptr->assets.door.open);
	}
	//if (c == 'C')
	//	return (ptr->assets.coin.a);
	if (c == 'X')
		return (ptr->assets.enemy);
	return (NULL);
}

void	init_assets_in_window(t_so_long *ptr)
{
	size_t	y;
	size_t	x;
	void	*asset;

	y = 1;//HERE
	while (ptr->map_2d[y])
	{
		x = 0;
		while (ptr->map_2d[y][x])
		{
			asset = get_asset(ptr, ptr->map_2d[y][x]);
			if (asset)
				mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, asset, x * 32, y * 32);
			x++;
		}
		y++;
	}
	x = 0;
	while (ptr->map_2d[0][x])
	{
		asset = get_asset(ptr, ptr->map_2d[0][x]);
		mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.black, x * 32, 0);
		x++;
	}
}

int dd(t_so_long *ptr)
{
	ft_printf("HI\n");
	return (0);
}

int	start_game(char *map)
{
	t_so_long	ptr;
	int w = 0;
	int h = 0;

	ptr.mlx = mlx_init();
	if (!ptr.mlx)
		return (1);
	ptr.mlx_win = mlx_new_window(ptr.mlx, (map_x_len(map)) * 32, (map_y_len(map) + 1) * 32, "BONUS");
	if (!ptr.mlx_win)
		return (mlx_destroy_display(ptr.mlx),1);
	ptr.map = map;
	if (create_2d_map(map, &ptr.map_2d))
		return (mlx_destroy_window(ptr.mlx, ptr.mlx_win), mlx_destroy_display(ptr.mlx),1);
	ptr.available_coins = count_available_coins(&ptr);
	ptr.exit = 1;
	ptr.flag = 1;
	ptr.counter = 0;
	ptr.last_pp = 3;
	get_exit_position(ptr.ep, &ptr);
	init_assets(&ptr);
	init_assets_in_window(&ptr);
	counter(&ptr);
	mlx_key_hook(ptr.mlx_win, handle_input, &ptr);
	mlx_hook(ptr.mlx_win, DestroyNotify, ButtonPressMask, destroy_all, &ptr);
	mlx_loop_hook(ptr.mlx, animations, &ptr);
	mlx_loop(ptr.mlx);
	return (0);
}
