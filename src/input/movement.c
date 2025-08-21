/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:38:59 by shutan            #+#    #+#             */
/*   Updated: 2025/08/21 18:39:00 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Move player to the left (strafe) */
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dy * 0.1;
	new_y = game->player.y + game->player.dx * 0.1;
	if (is_valid_position(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

/* Move player to the right (strafe) */
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dy * 0.1;
	new_y = game->player.y - game->player.dx * 0.1;
	if (is_valid_position(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

/* Rotate player view to the right */
void	rotate_right(t_game *game)
{
	game->player.angle += 0.1;
	if (game->player.angle >= 2 * PI)
		game->player.angle -= 2 * PI;
	game->player.dx = cos(game->player.angle);
	game->player.dy = sin(game->player.angle);
}

/* Check if position is valid (not a wall) */
int	is_valid_position(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->map_width)
		return (0);
	if (map_y < 0 || map_y >= game->map_height)
		return (0);
	if (game->map[map_y][map_x] == '1')
		return (0);
	return (1);
}
