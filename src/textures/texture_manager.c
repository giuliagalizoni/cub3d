/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 02:00:00 by shutan            #+#    #+#             */
/*   Updated: 2025/09/05 07:01:23 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Get texture based on wall side and ray direction */
t_img	*get_wall_texture(t_game *game, int wall_side)
{
	(void)game;
	if (wall_side == 0)
		return (&game->textures->imgs[0]);
	else
		return (&game->textures->imgs[2]);
}

/* Get texture based on wall side and ray direction with improved logic */
t_img	*get_wall_texture_advanced(t_game *game, int wall_side,
			double ray_angle)
{
	double	ray_dir_x;
	double	ray_dir_y;

	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	if (wall_side == 0)
	{
		if (ray_dir_x > 0)
			return (&game->textures->imgs[3]);
		else
			return (&game->textures->imgs[2]);
	}
	else
	{
		if (ray_dir_y > 0)
			return (&game->textures->imgs[0]);
		else
			return (&game->textures->imgs[1]);
	}
}

/* Get texture based on wall side and ray direction using standard method */
t_img	*get_wall_texture_by_direction(t_game *game, int wall_side,
			double ray_dir_x, double ray_dir_y)
{
	if (wall_side == 0)
	{
		if (ray_dir_x < 0)
			return (&game->textures->imgs[2]);
		else
			return (&game->textures->imgs[3]);
	}
	else
	{
		if (ray_dir_y > 0)
			return (&game->textures->imgs[1]);
		else
			return (&game->textures->imgs[0]);
	}
}
