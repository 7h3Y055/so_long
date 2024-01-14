#include "so_long_bonus.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*map;

	if (argc != 2)
		return (ft_putendl_fd("[-] Usage:\n./so_long_bonus <MAP>.ber", 2), 1);
	if (!ft_strrchr(argv[1], '.') || \
			ft_strncmp(ft_strrchr(argv[1], '.'), ".ber", 5))
		return (ft_putendl_fd("[!] file extention was not .ber", 2), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (perror(argv[1]), 1);
	map = read_and_check_map(fd);
	if (!map)
		return (1);
	return (start_game(map));
}
