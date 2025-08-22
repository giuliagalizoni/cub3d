#include "../includes/cub3d.h"

void	init(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->player = NULL;
	game->textures = malloc(sizeof(t_textures));
    if (!game->textures)
        return ; // error handling
    game->textures->NO = NULL;
    game->textures->SO = NULL;
    game->textures->WE = NULL;
    game->textures->EA = NULL;
	game->map = NULL;
}

int	main (int ac, char **av)
{
	t_game game;

	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./cub3d file.cub\n", 2);
		return (1);
	}

	init(&game);
	parser(av[1], &game);

	ft_printf("NO: %s\n", game.textures->NO);
	ft_printf("SO: %s\n", game.textures->SO);
	ft_printf("WE: %s\n", game.textures->WE);
	ft_printf("EA: %s\n", game.textures->EA);

	return (0);
}
