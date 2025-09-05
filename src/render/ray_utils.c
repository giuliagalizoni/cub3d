/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 06:45:13 by shutan            #+#    #+#             */
/*   Updated: 2025/09/05 07:01:23 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	calculate_ray_angle(t_game *game, int x)
{
	double	camera_x;
	double	ray_angle;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray_angle = game->player->angle + atan(camera_x * tan(FOV * DR / 2));
	return (ray_angle);
}

double	cast_single_ray(t_game *game, double ray_angle)
{
	double	ray_x;
	double	ray_y;
	double	dx;
	double	dy;
	double	distance;

	ray_x = game->player->x;
	ray_y = game->player->y;
	dx = cos(ray_angle) * 0.01;
	dy = sin(ray_angle) * 0.01;
	distance = 0;
	while (!is_wall(game, (int)ray_x, (int)ray_y))
	{
		ray_x += dx;
		ray_y += dy;
		distance += 0.01;
	}
	return (distance * cos(ray_angle - game->player->angle));
}

double	calculate_wall_height(double distance)
{
	double	wall_height;

	if (distance <= 0)
		return (WIN_HEIGHT);
	wall_height = WIN_HEIGHT / distance;
	if (wall_height > WIN_HEIGHT)
		wall_height = WIN_HEIGHT;
	return (wall_height);
}

double	perform_dda_loop(t_game *game, t_dda_vars *vars, int *wall_side)
{
	while (vars->hit == 0)
	{
		if (vars->side_dist_x < vars->side_dist_y)
		{
			vars->side_dist_x += vars->delta_dist_x;
			vars->map_x += vars->step_x;
			*wall_side = 0;
		}
		else
		{
			vars->side_dist_y += vars->delta_dist_y;
			vars->map_y += vars->step_y;
			*wall_side = 1;
		}
		if (is_wall(game, vars->map_x, vars->map_y))
			vars->hit = 1;
	}
	if (*wall_side == 0)
		return (vars->side_dist_x - vars->delta_dist_x);
	else
		return (vars->side_dist_y - vars->delta_dist_y);
}
