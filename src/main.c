#include "../include/cub3d.h"

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

/* Initialize game with test map */
void	init_test_game(t_game *game)
{
	static char	*test_map[] = {
		"111111111",
		"100000001",
		"101010101",
		"100000001",
		"100N00001",
		"100000001",
		"101010101",
		"100000001",
		"111111111",
		NULL
	};

	game->map->arr = test_map;
	game->map->width = 9;
	game->map->height = 9;
	init_player(game, 3, 4, 'N');
	set_default_colors(game);
}

/* Main function */
int	main(int ac, char **av)
{
	t_game	game;

		if (ac != 2)
	{
		ft_putstr_fd("Usage: ./cub3d file.cub\n", 2);
		return (1);
	}

	init(&game);
	parser(av[1], &game);

	// DEBUG
	ft_printf("NO: %s\n", game.textures->NO);
	ft_printf("SO: %s\n", game.textures->SO);
	ft_printf("WE: %s\n", game.textures->WE);
	ft_printf("EA: %s\n", game.textures->EA);

	init_test_game(&game);
	if (!init_window(&game))
		return (1);
	if (!init_screen_image(&game))
		return (1);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
