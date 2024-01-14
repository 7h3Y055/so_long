#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include "so_long_bonus.h"

void	counter(t_so_long *ptr)
{
	char *number;
	int		i;
	int		x;

	number = ft_itoa(ptr->counter);	
	x = (map_x_len(ptr->map) - 1) / 2 + (ft_strlen(number) / 2);
	i = ft_strlen(number) - 1;
	while (i >= 0)
	{
		if (number[i] == '0')
			mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.num.zero, ((x ) * 32) + 14, 8);
		if (number[i] == '1')
			mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.num.one, ((x ) * 32) + 14, 8);
		if (number[i] == '2')
			mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.num.two, ((x ) * 32) + 14, 8);
		if (number[i] == '3')
			mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.num.three, ((x ) * 32) + 14, 8);
		if (number[i] == '4')
			mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.num.foor, ((x ) * 32) + 14, 8);
		if (number[i] == '5')
			mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.num.five, ((x ) * 32) + 14, 8);
		if (number[i] == '6')
			mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.num.six, ((x ) * 32) + 14, 8);
		if (number[i] == '7')
			mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.num.seven, ((x ) * 32) + 14, 8);
		if (number[i] == '8')
			mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.num.eight, ((x ) * 32) + 14, 8);
		if (number[i] == '9')
			mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->assets.num.nine, ((x ) * 32) + 14, 8);
		x--;
		i--;
	}
	free(number);
}
