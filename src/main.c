/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalizon <ggalizon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 06:10:00 by shutan            #+#    #+#             */
/*   Updated: 2025/10/13 14:29:11 by ggalizon         ###   ########.fr       */
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
	game->mlx = NULL;
	game->win = NULL;
	game->screen.img = NULL;
	game->minimap.img = NULL;
	init_textures(game);
	init_map(game);
	init_keys(game);
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
	init_window(&game);
	setup_game(&game);
	init_minimap(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
