#include "../include/cub3d.h"

void	init(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return ; // error handling
	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
		return ; // error handling
	game->textures->NO = NULL;
	game->textures->SO = NULL;
	game->textures->WE = NULL;
	game->textures->EA = NULL;
	game->textures->C = -1;
	game->textures->F = -1;
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return ; // error handling
	game->map->arr = NULL;
	game->map->player_x = -1;
	game->map->player_x = -1;
	game->map->player_dir = '\0';
	
	// Initialize key states
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
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
	// set_default_colors(game);
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
	ft_printf("F: %d\n", game.textures->F);
	ft_printf("C: %d\n", game.textures->C);

	ft_printf("\n## MAP ARR##\n");
	for (int i = 0; game.map->arr[i]; i++)
		ft_printf("%s\n", game.map->arr[i]);

	ft_printf("map height: %d\n", game.map->height);
	ft_printf("map width: %d\n", game.map->width);
	ft_printf("player position x: %d\n", game.map->player_x);
	ft_printf("player position y: %d\n", game.map->player_y);
	ft_printf("player direction: %c\n", game.map->player_dir);

	// init_test_game(&game);
	init_player(&game, game.map->player_x, game.map->player_y, game.map->player_dir);
	if (!init_window(&game))
		return (1);

	// conversion of rgb to mlx format -- decide where this fits better
	game.textures->F = mlx_get_color_value(game.mlx, game.textures->F);
    game.textures->C = mlx_get_color_value(game.mlx, game.textures->C);

	if (!init_screen_image(&game))
		return (1);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
