/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:39:11 by shutan            #+#    #+#             */
/*   Updated: 2025/09/04 18:45:14 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Cast rays for each column of the screen */
void	cast_rays(t_game *game)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	wall_dist;
	double	wall_height;
	int		wall_side;
	double	wall_x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		// Calculate camera position (-1 to 1)
		camera_x = 2 * x / (double)WIN_WIDTH - 1;

		// Calculate ray direction
		ray_dir_x = game->player->dx + game->player->plane_x * camera_x;
		ray_dir_y = game->player->dy + game->player->plane_y * camera_x;

		wall_dist = cast_ray_dda_standard(game, ray_dir_x, ray_dir_y, &wall_side, &wall_x);
		// Use the same wall height calculation as the working project
		wall_height = (int)(WIN_HEIGHT / wall_dist);
		draw_wall_slice_textured(game, x, wall_height, wall_side, ray_dir_x, ray_dir_y, wall_x);
		x++;
	}
}

/* Calculate the angle for a specific ray */
double	calculate_ray_angle(t_game *game, int x)
{
	double	camera_x;
	double	ray_angle;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray_angle = game->player->angle + atan(camera_x * tan(FOV * DR / 2));
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

/* Cast ray with DDA algorithm using standard ray direction */
double	cast_ray_dda_standard(t_game *game, double ray_dir_x, double ray_dir_y, int *wall_side, double *wall_x)
{
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	double	perp_wall_dist;

	map_x = (int)game->player->x;
	map_y = (int)game->player->y;
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	hit = 0;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (game->player->x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - game->player->x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (game->player->y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - game->player->y) * delta_dist_y;
	}
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			*wall_side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			*wall_side = 1;
		}
		if (is_wall(game, map_x, map_y))
			hit = 1;
	}
	// Calculate perpendicular wall distance
	if (*wall_side == 0)
		perp_wall_dist = (side_dist_x - delta_dist_x);
	else
		perp_wall_dist = (side_dist_y - delta_dist_y);

	// Calculate wall_x for texture mapping
	if (*wall_side == 0)
		*wall_x = game->player->y + perp_wall_dist * ray_dir_y;
	else
		*wall_x = game->player->x + perp_wall_dist * ray_dir_x;
	*wall_x -= floor(*wall_x);
	return (perp_wall_dist);
}

/* Calculate wall height based on distance */
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
