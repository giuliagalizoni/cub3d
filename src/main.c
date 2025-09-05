/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 06:10:00 by shutan            #+#    #+#             */
/*   Updated: 2025/09/05 06:45:13 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


static void	init_textures(t_game *game)
{
	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
		error_exit(ERR_MALLOC, game, "textures");
	game->textures->no = NULL;
	game->textures->so = NULL;
	game->textures->we = NULL;
	game->textures->ea = NULL;
	game->textures->c = -1;
	game->textures->f = -1;
	game->textures->loaded = 0;
}

static void	init_map(t_game *game)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		error_exit(ERR_MALLOC, game, "map");
	game->map->arr = NULL;
	game->map->player_x = -1;
	game->map->player_y = -1;
	game->map->player_dir = '\0';
	game->map->player_x = -1;
	game->map->player_x = -1;
	game->map->player_dir = '\0';
}

static void	init_keys(t_game *game)
{
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
}

static void	init(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		error_exit(ERR_MALLOC, game, "player");
	game->screen.img = NULL;
	game->win = NULL;
	init_textures(game);
	init_map(game);
	init_keys(game);
}

/* Main function */
static void debug_prints(t_game game)
{
	ft_printf("NO: %s\n", game.textures->NO);
	ft_printf("SO: %s\n", game.textures->SO);
	ft_printf("WE: %s\n", game.textures->WE);
	ft_printf("EA: %s\n", game.textures->EA);
	ft_printf("F: %d\n", game.textures->F);
	ft_printf("C: %d\n", game.textures->C);

	ft_printf("\n## MAP ARR##\n");
	for (int i = 0; game.map->arr[i]; i++)
		ft_printf("%s\n", game.map->arr[i]);
	ft_printf("\n");
	ft_printf("map height: %d\n", game.map->height);
	ft_printf("map width: %d\n", game.map->width);
	ft_printf("player position x: %d\n", game.map->player_x);
	ft_printf("player position y: %d\n", game.map->player_y);
	ft_printf("player direction: %c\n", game.map->player_dir);
}

/* Main function */
int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		ft_perror(ERR_USAGE, NULL);
		return (1);
	}
	init(&game);
	parser(av[1], &game);
	init_player(&game, game.map->player_x, game.map->player_y,
		game.map->player_dir);

	if (!init_window(&game))
	{
		cleanup_parsing(&game);
		return (1);
	}
	debug_prints(game);
	if (!setup_game(&game))
  {
		cleanup_parsing(&game);
		return (1);
	}
	// conversion of rgb to mlx format -- decide where this fits better
	game.textures->F = mlx_get_color_value(game.mlx, game.textures->F);
	game.textures->C = mlx_get_color_value(game.mlx, game.textures->C);
	if (!init_screen_image(&game))
	{
		cleanup_parsing(&game);
		return (1);
	}
	setup_hooks(&game);
	mlx_loop(game.mlx);
	cleanup_parsing(&game);
	return (0);
}
