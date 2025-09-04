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
		game->keys.w = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	return (0);
}

/* Handle key release events */
int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

/* Update movement based on current key states */
void	update_movement(t_game *game)
{
	// Handle rotation first
	if (game->keys.left)
		rotate_left(game);
	if (game->keys.right)
		rotate_right(game);
	
	// Handle movement
	if (game->keys.w)
		move_forward(game);
	if (game->keys.s)
		move_backward(game);
	if (game->keys.a)
		move_left(game);
	if (game->keys.d)
		move_right(game);
}

/* Move player forward */
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player->x + game->player->dx * MOVE_SPEED;
	new_y = game->player->y + game->player->dy * MOVE_SPEED;
	if (!check_collision(game, new_x, new_y))
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

	new_x = game->player->x - game->player->dx * MOVE_SPEED;
	new_y = game->player->y - game->player->dy * MOVE_SPEED;
	if (!check_collision(game, new_x, new_y))
	{
		game->player->x = new_x;
		game->player->y = new_y;
	}
}

/* Rotate player view to the left */
void	rotate_left(t_game *game)
{
	game->player->angle -= ROTATION_SPEED;
	if (game->player->angle < 0)
		game->player->angle += 2 * PI;
	game->player->dx = cos(game->player->angle);
	game->player->dy = sin(game->player->angle);
}
