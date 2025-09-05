/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:39:11 by shutan            #+#    #+#             */
/*   Updated: 2025/09/05 05:50:43 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	determine_wall_side(t_game *game, double ray_angle, int map_x, int map_y)
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		side;

	(void)game;
	(void)map_x;
	(void)map_y;
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	if (fabs(ray_dir_x) > fabs(ray_dir_y))
	{
		if (ray_dir_x > 0)
			side = 3;
		else
			side = 2;
	}
	else
	{
		if (ray_dir_y > 0)
			side = 1;
		else
			side = 0;
	}
	return (side);
}

static double	calculate_perp_dist(t_game *game, int wall_side,
		t_wall_calc *calc)
{
	double	perp_wall_dist;

	if (wall_side == 0)
		perp_wall_dist = (calc->map_x - game->player->x + (1 - calc->step_x)
				/ 2.0) / calc->ray_dir_x;
	else
		perp_wall_dist = (calc->map_y - game->player->y + (1 - calc->step_y)
				/ 2.0) / calc->ray_dir_y;
	return (perp_wall_dist);
}

double	calculate_wall_x(t_game *game, double ray_angle, int wall_side)
{
	double		wall_x;
	double		perp_wall_dist;
	t_wall_calc	calc;

	calc.ray_dir_x = cos(ray_angle);
	calc.ray_dir_y = sin(ray_angle);
	calc.map_x = (int)game->player->x;
	calc.map_y = (int)game->player->y;
	if (calc.ray_dir_x < 0)
		calc.step_x = -1;
	else
		calc.step_x = 1;
	if (calc.ray_dir_y < 0)
		calc.step_y = -1;
	else
		calc.step_y = 1;
	perp_wall_dist = calculate_perp_dist(game, wall_side, &calc);
	if (wall_side == 0)
		wall_x = game->player->y + perp_wall_dist * calc.ray_dir_y;
	else
		wall_x = game->player->x + perp_wall_dist * calc.ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	validate_texture_file(char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}
