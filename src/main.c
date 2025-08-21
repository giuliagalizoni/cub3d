/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:23:46 by shutan            #+#    #+#             */
/*   Updated: 2025/08/21 18:24:12 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

	game->map = test_map;
	game->map_width = 9;
	game->map_height = 9;
	init_player(game, 3, 4, 'N');
	set_default_colors(game);
}

/* Main function */
int	main(void)
{
	t_game	game;

	init_test_game(&game);
	if (!init_window(&game))
		return (1);
	if (!init_screen_image(&game))
		return (1);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
