/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliagalizoni <giuliagalizoni@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:38:51 by shutan            #+#    #+#             */
/*   Updated: 2025/08/22 12:09:42 by giuliagal      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Handle key press events */
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		move_forward(game);
	else if (keycode == KEY_S)
		move_backward(game);
	else if (keycode == KEY_A)
		move_left(game);
	else if (keycode == KEY_D)
		move_right(game);
	else if (keycode == KEY_LEFT)
		rotate_left(game);
	else if (keycode == KEY_RIGHT)
		rotate_right(game);
	return (0);
}

/* Move player forward */
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player->x + game->player->dx * 0.1;
	new_y = game->player->y + game->player->dy * 0.1;
	if (is_valid_position(game, new_x, new_y))
	{
		game->player->x = new_x;
		game->player->y = new_y;
	}
}

/* Move player backward */
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player->x - game->player->dx * 0.1;
	new_y = game->player->y - game->player->dy * 0.1;
	if (is_valid_position(game, new_x, new_y))
	{
		game->player->x = new_x;
		game->player->y = new_y;
	}
}

/* Rotate player view to the left */
void	rotate_left(t_game *game)
{
	game->player->angle -= 0.1;
	if (game->player->angle < 0)
		game->player->angle += 2 * PI;
	game->player->dx = cos(game->player->angle);
	game->player->dy = sin(game->player->angle);
}
