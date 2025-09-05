/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 06:40:41 by shutan            #+#    #+#             */
/*   Updated: 2025/09/05 06:46:24 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_player(t_game *game, double x, double y, char direction)
{
	game->player->x = x + 0.5;
	game->player->y = y + 0.5;
	set_player_direction(game->player, direction);
}

int	setup_game(t_game *game)
{
	game->floor_color = mlx_get_color_value(game->mlx, game->textures->f);
	game->ceiling_color = mlx_get_color_value(game->mlx, game->textures->c);
	if (!load_all_textures(game))
	{
		ft_printf("Error: Failed to load textures\n");
		cleanup_parsing(game);
		return (0);
	}
	if (!init_screen_image(game))
	{
		cleanup_parsing(game);
		return (0);
	}
	return (1);
}

void	cleanup_game(t_game *game)
{
	if (game->textures && game->textures->loaded)
		free_textures(game);
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
}
