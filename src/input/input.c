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
	if (game->keys.left)
		rotate_left(game);
	if (game->keys.right)
		rotate_right(game);
	if (game->keys.w)
		move_forward(game);
	if (game->keys.s)
		move_backward(game);
	if (game->keys.a)
		move_left(game);
	if (game->keys.d)
		move_right(game);
}

/* Rotate player view to the left */
void	rotate_left(t_game *game)
{
	double	old_dx;
	double	old_plane_x;

	old_dx = game->player->dx;
	old_plane_x = game->player->plane_x;
	game->player->angle -= ROTATION_SPEED;
	if (game->player->angle < 0)
		game->player->angle += 2 * PI;
	game->player->dx = old_dx * cos(-ROTATION_SPEED) - game->player->dy
		* sin(-ROTATION_SPEED);
	game->player->dy = old_dx * sin(-ROTATION_SPEED) + game->player->dy
		* cos(-ROTATION_SPEED);
	game->player->plane_x = old_plane_x * cos(-ROTATION_SPEED)
		- game->player->plane_y * sin(-ROTATION_SPEED);
	game->player->plane_y = old_plane_x * sin(-ROTATION_SPEED)
		+ game->player->plane_y * cos(-ROTATION_SPEED);
}
