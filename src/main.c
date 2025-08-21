#include "../includes/cub3d.h"

int	main (int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./cub3d file.cub\n", 2);
		return (1);
	}

	printf("%s\n", av[1]);
	return (0);
}
