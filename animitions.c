#include "minilibx-linux/mlx.h"
#include "so_long_bonus.h"


void	coin_animition(t_so_long *ptr, int *coin_speed)
{
	static int	n;
	int			cp[2];
	void		*asset;

	*coin_speed = 0;
	if (n == 0)
		asset = ptr->assets.coin.a;
	if (n == 1)
		asset = ptr->assets.coin.b;
	if (n == 2)
		asset = ptr->assets.coin.c;
	if (n == 3)
		asset = ptr->assets.coin.d;
	if (n == 4)
		asset = ptr->assets.coin.e;
	if (n == 5)
		asset = ptr->assets.coin.f;
	if (n == 6)
		asset = ptr->assets.coin.g;
	if (n == 7)
		asset = ptr->assets.coin.h;
	cp[0] = 0;
	while (ptr->map_2d[cp[0]])
	{
		cp[1] = 0;
		while (ptr->map_2d[cp[0]][cp[1]])
		{
			if (ptr->map_2d[cp[0]][cp[1]] == 'C')
			{
				mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, asset, cp[1] * 32, cp[0] * 32);
			}
			cp[1]++;
		}
		cp[0]++;
	}
	if (n == 7)
		n = 0;
	else
		n++;
}
