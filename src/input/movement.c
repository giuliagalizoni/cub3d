/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:38:59 by shutan            #+#    #+#             */
/*   Updated: 2025/10/13 18:23:17 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Move player to the left (strafe) */
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	double	final_x;
	double	final_y;

	new_x = game->player->x + game->player->dy * MOVE_SPEED;
	new_y = game->player->y - game->player->dx * MOVE_SPEED;
	check_sliding_collision(game, new_x, new_y, &final_x, &final_y);
	game->player->x = final_x;
	game->player->y = final_y;
}

/* Move player to the right (strafe) */
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	double	final_x;
	double	final_y;

	new_x = game->player->x - game->player->dy * MOVE_SPEED;
	new_y = game->player->y + game->player->dx * MOVE_SPEED;
	check_sliding_collision(game, new_x, new_y, &final_x, &final_y);
	game->player->x = final_x;
	game->player->y = final_y;
}

/* Rotate player view to the right */
void	rotate_right(t_game *game)
{
	double	old_dx;
	double	old_plane_x;

	old_dx = game->player->dx;
	old_plane_x = game->player->plane_x;
	game->player->angle += ROTATION_SPEED;
	if (game->player->angle >= 2 * PI)
		game->player->angle -= 2 * PI;
	game->player->dx = old_dx * cos(ROTATION_SPEED) - game->player->dy
		* sin(ROTATION_SPEED);
	game->player->dy = old_dx * sin(ROTATION_SPEED) + game->player->dy
		* cos(ROTATION_SPEED);
	game->player->plane_x = old_plane_x * cos(ROTATION_SPEED)
		- game->player->plane_y * sin(ROTATION_SPEED);
	game->player->plane_y = old_plane_x * sin(ROTATION_SPEED)
		+ game->player->plane_y * cos(ROTATION_SPEED);
}

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	final_x;
	double	final_y;

	new_x = game->player->x + game->player->dx * MOVE_SPEED;
	new_y = game->player->y + game->player->dy * MOVE_SPEED;
	check_sliding_collision(game, new_x, new_y, &final_x, &final_y);
	game->player->x = final_x;
	game->player->y = final_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	double	final_x;
	double	final_y;

	new_x = game->player->x - game->player->dx * MOVE_SPEED;
	new_y = game->player->y - game->player->dy * MOVE_SPEED;
	check_sliding_collision(game, new_x, new_y, &final_x, &final_y);
	game->player->x = final_x;
	game->player->y = final_y;
}
