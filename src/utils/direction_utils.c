/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 06:40:41 by shutan            #+#    #+#             */
/*   Updated: 2025/09/05 06:45:13 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_north_direction(t_player *player)
{
	player->angle = 3 * PI / 2;
	player->dx = 0;
	player->dy = -1;
	player->plane_x = 0.66;
	player->plane_y = 0;
}

static void	set_south_direction(t_player *player)
{
	player->angle = PI / 2;
	player->dx = 0;
	player->dy = 1;
	player->plane_x = -0.66;
	player->plane_y = 0;
}

static void	set_east_direction(t_player *player)
{
	player->angle = 0;
	player->dx = 1;
	player->dy = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
}

static void	set_west_direction(t_player *player)
{
	player->angle = PI;
	player->dx = -1;
	player->dy = 0;
	player->plane_x = 0;
	player->plane_y = -0.66;
}

void	set_player_direction(t_player *player, char direction)
{
	if (direction == 'N')
		set_north_direction(player);
	else if (direction == 'S')
		set_south_direction(player);
	else if (direction == 'E')
		set_east_direction(player);
	else if (direction == 'W')
		set_west_direction(player);
}
