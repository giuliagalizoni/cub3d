/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:39:11 by shutan            #+#    #+#             */
/*   Updated: 2025/08/21 18:39:14 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Cast rays for each column of the screen */
void	cast_rays(t_game *game)
{
	int		x;
	double	ray_angle;
	double	distance;
	double	wall_height;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ray_angle = calculate_ray_angle(game, x);
		distance = cast_single_ray(game, ray_angle);
		wall_height = calculate_wall_height(distance);
		draw_wall_slice(game, x, wall_height);
		x++;
	}
}

/* Calculate the angle for a specific ray */
double	calculate_ray_angle(t_game *game, int x)
{
	double	camera_x;
	double	ray_angle;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray_angle = game->player.angle + atan(camera_x * tan(FOV * DR / 2));
	return (ray_angle);
}

/* Cast a single ray and return distance to wall */
double	cast_single_ray(t_game *game, double ray_angle)
{
	double	ray_x;
	double	ray_y;
	double	dx;
	double	dy;
	double	distance;

	ray_x = game->player.x;
	ray_y = game->player.y;
	dx = cos(ray_angle) * 0.01;
	dy = sin(ray_angle) * 0.01;
	distance = 0;
	while (!is_wall(game, (int)ray_x, (int)ray_y))
	{
		ray_x += dx;
		ray_y += dy;
		distance += 0.01;
	}
	return (distance * cos(ray_angle - game->player.angle));
}

/* Calculate wall height based on distance */
double	calculate_wall_height(double distance)
{
	if (distance == 0)
		return (WIN_HEIGHT);
	return (WIN_HEIGHT / distance);
}
