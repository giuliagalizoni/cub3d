/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 02:00:00 by shutan            #+#    #+#             */
/*   Updated: 2025/09/04 16:48:05 by shutan           ###   ########.fr       */
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
t_img	*get_wall_texture_advanced(t_game *game, int wall_side, double ray_angle)
{
	double	ray_dir_x;
	double	ray_dir_y;
	
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	
	// wall_side: 0 = East/West wall (vertical), 1 = North/South wall (horizontal)
	// 根据ray的方向确定wall的实际方向，然后选择对应的texture
	if (wall_side == 0) // East/West wall (vertical)
	{
		if (ray_dir_x > 0)
			return (&game->textures->imgs[3]); // East texture (ray going east, hitting east wall)
		else
			return (&game->textures->imgs[2]); // West texture (ray going west, hitting west wall)
	}
	else // North/South wall (horizontal)
	{
		if (ray_dir_y > 0)
			return (&game->textures->imgs[0]); // North texture (ray going north, hitting north wall)
		else
			return (&game->textures->imgs[1]); // South texture (ray going south, hitting south wall)
	}
}

/* Get texture based on wall type and direction */
t_img	*get_wall_texture_by_type(t_game *game, char wall_type, int wall_side, double ray_angle)
{
	t_img	*base_texture;
	
	base_texture = get_wall_texture_advanced(game, wall_side, ray_angle);
	if (wall_type == '1')
		return (base_texture);
	else if (wall_type == '2')
		return (&game->textures->imgs[0]);
	else if (wall_type == '3')
		return (&game->textures->imgs[1]);
	else if (wall_type == '4')
		return (&game->textures->imgs[2]);
	else
		return (base_texture);
}

/* Calculate texture X coordinate */
int	calculate_texture_x(t_img *texture, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)texture->width);
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

/* Calculate texture Y coordinate */
int	calculate_texture_y(t_img *texture, int y, int wall_start, int wall_height)
{
	int	tex_y;
	int	relative_y;

	relative_y = y - wall_start;
	if (wall_height <= 0)
		return (0);
	tex_y = (relative_y * texture->height) / wall_height;
	if (tex_y < 0)
		tex_y = 0;
	else if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	return (tex_y);
}

/* Get pixel color from texture */
int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*dst;
	int		color;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
}