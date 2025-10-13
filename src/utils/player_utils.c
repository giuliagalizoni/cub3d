/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:09:16 by shutan            #+#    #+#             */
/*   Updated: 2025/10/13 13:11:02 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_player_north(t_player *player)
{
	player->angle = 3 * PI / 2;
	player->dx = 0;
	player->dy = -1;
	player->plane_x = 0.66;
	player->plane_y = 0;
}

static void	set_player_south(t_player *player)
{
	player->angle = PI / 2;
	player->dx = 0;
	player->dy = 1;
	player->plane_x = -0.66;
	player->plane_y = 0;
}

static void	set_player_east(t_player *player)
{
	player->angle = 0;
	player->dx = 1;
	player->dy = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
}

static void	set_player_west(t_player *player)
{
	player->angle = PI;
	player->dx = -1;
	player->dy = 0;
	player->plane_x = 0;
	player->plane_y = -0.66;
}

void	init_player(t_game *game, double x, double y, char direction)
{
	game->player->x = x + 0.5;
	game->player->y = y + 0.5;
	if (direction == 'N')
		set_player_north(game->player);
	else if (direction == 'S')
		set_player_south(game->player);
	else if (direction == 'E')
		set_player_east(game->player);
	else if (direction == 'W')
		set_player_west(game->player);
}
