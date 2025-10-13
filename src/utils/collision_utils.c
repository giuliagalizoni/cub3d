/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:17:37 by shutan            #+#    #+#             */
/*   Updated: 2025/10/13 18:28:15 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_valid_position(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->map->width)
		return (0);
	if (map_y < 0 || map_y >= game->map->height)
		return (0);
	if (game->map->arr[map_y][map_x] == '1')
		return (0);
	return (1);
}

int	check_collision(t_game *game, double x, double y)
{
	double	radius;
	int		check_x;
	int		check_y;

	radius = 0.2;
	check_x = (int)(x - radius);
	check_y = (int)(y - radius);
	if (!is_valid_position(game, check_x, check_y))
		return (1);
	check_x = (int)(x + radius);
	check_y = (int)(y - radius);
	if (!is_valid_position(game, check_x, check_y))
		return (1);
	check_x = (int)(x - radius);
	check_y = (int)(y + radius);
	if (!is_valid_position(game, check_x, check_y))
		return (1);
	check_x = (int)(x + radius);
	check_y = (int)(y + radius);
	if (!is_valid_position(game, check_x, check_y))
		return (1);
	return (0);
}

static int	check_axis_movement(t_game *game, t_slide_params *params)
{
	double	old_x;
	double	old_y;
	int		x_collision;
	int		y_collision;

	old_x = game->player->x;
	old_y = game->player->y;
	x_collision = check_collision(game, params->new_x, old_y);
	y_collision = check_collision(game, old_x, params->new_y);
	if (!x_collision && y_collision)
	{
		params->final_x = params->new_x;
		params->final_y = old_y;
		return (0);
	}
	if (x_collision && !y_collision)
	{
		params->final_x = old_x;
		params->final_y = params->new_y;
		return (0);
	}
	params->final_x = old_x;
	params->final_y = old_y;
	return (1);
}

int	check_sliding_collision(t_game *game, t_slide_params *params)
{
	if (!check_collision(game, params->new_x, params->new_y))
	{
		params->final_x = params->new_x;
		params->final_y = params->new_y;
		return (0);
	}
	return (check_axis_movement(game, params));
}
