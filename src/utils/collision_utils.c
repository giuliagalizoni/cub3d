/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:17:37 by shutan            #+#    #+#             */
/*   Updated: 2025/10/13 18:21:31 by shutan           ###   ########.fr       */
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

/* 滑动碰撞检测 - 允许沿着墙面滑行 */
int	check_sliding_collision(t_game *game, double new_x, double new_y, double *final_x, double *final_y)
{
	double	old_x;
	double	old_y;
	int		x_collision;
	int		y_collision;

	old_x = game->player->x;
	old_y = game->player->y;
	
	/* 检查完整移动是否有碰撞 */
	if (!check_collision(game, new_x, new_y))
	{
		*final_x = new_x;
		*final_y = new_y;
		return (0);
	}
	
	/* 分别检查X轴和Y轴移动 */
	x_collision = check_collision(game, new_x, old_y);
	y_collision = check_collision(game, old_x, new_y);
	
	/* 如果X轴可以移动，Y轴不能移动，只移动X轴 */
	if (!x_collision && y_collision)
	{
		*final_x = new_x;
		*final_y = old_y;
		return (0);
	}
	
	/* 如果Y轴可以移动，X轴不能移动，只移动Y轴 */
	if (x_collision && !y_collision)
	{
		*final_x = old_x;
		*final_y = new_y;
		return (0);
	}
	
	/* 如果两个轴都不能移动，保持原位置 */
	*final_x = old_x;
	*final_y = old_y;
	return (1);
}
