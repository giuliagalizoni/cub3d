/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:39:11 by shutan            #+#    #+#             */
/*   Updated: 2025/09/05 05:38:03 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	process_single_ray(t_game *game, int x, t_ray_data *ray_data)
{
	double	camera_x;
	double	wall_dist;
	double	wall_height;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray_data->ray_dir_x = game->player->dx + game->player->plane_x * camera_x;
	ray_data->ray_dir_y = game->player->dy + game->player->plane_y * camera_x;
	wall_dist = cast_ray_dda_standard(game, ray_data);
	wall_height = (int)(WIN_HEIGHT / wall_dist);
	draw_wall_slice_textured(game, x, wall_height, ray_data);
}

void	cast_rays(t_game *game)
{
	int			x;
	t_ray_data	ray_data;

	x = 0;
	while (x < WIN_WIDTH)
	{
		process_single_ray(game, x, &ray_data);
		x++;
	}
}

static void	init_dda_vars(t_game *game, double ray_dir_x, double ray_dir_y,
		t_dda_vars *vars)
{
	vars->map_x = (int)game->player->x;
	vars->map_y = (int)game->player->y;
	vars->delta_dist_x = fabs(1 / ray_dir_x);
	vars->delta_dist_y = fabs(1 / ray_dir_y);
	vars->hit = 0;
}

static void	set_step_and_side(t_game *game, double ray_dir_x, double ray_dir_y,
		t_dda_vars *vars)
{
	if (ray_dir_x < 0)
	{
		vars->step_x = -1;
		vars->side_dist_x = (game->player->x - vars->map_x)
			* vars->delta_dist_x;
	}
	else
	{
		vars->step_x = 1;
		vars->side_dist_x = (vars->map_x + 1.0 - game->player->x)
			* vars->delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		vars->step_y = -1;
		vars->side_dist_y = (game->player->y - vars->map_y)
			* vars->delta_dist_y;
	}
	else
	{
		vars->step_y = 1;
		vars->side_dist_y = (vars->map_y + 1.0 - game->player->y)
			* vars->delta_dist_y;
	}
}

double	cast_ray_dda_standard(t_game *game, t_ray_data *ray_data)
{
	t_dda_vars	vars;
	double		perp_wall_dist;

	init_dda_vars(game, ray_data->ray_dir_x, ray_data->ray_dir_y, &vars);
	set_step_and_side(game, ray_data->ray_dir_x, ray_data->ray_dir_y, &vars);
	perp_wall_dist = perform_dda_loop(game, &vars, &ray_data->wall_side);
	if (ray_data->wall_side == 0)
		ray_data->wall_x = game->player->y + perp_wall_dist
			* ray_data->ray_dir_y;
	else
		ray_data->wall_x = game->player->x + perp_wall_dist
			* ray_data->ray_dir_x;
	ray_data->wall_x -= floor(ray_data->wall_x);
	return (perp_wall_dist);
}
