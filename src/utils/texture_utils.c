/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:17:53 by shutan            #+#    #+#             */
/*   Updated: 2025/10/13 13:17:59 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*dst;
	int		color;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

t_img	*get_wall_texture_by_type(t_game *game, char wall_type,
		int wall_side, double ray_angle)
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
