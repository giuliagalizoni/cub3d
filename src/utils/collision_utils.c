/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:17:37 by shutan            #+#    #+#             */
/*   Updated: 2025/10/13 13:17:38 by shutan           ###   ########.fr       */
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
