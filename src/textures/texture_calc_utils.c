/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_calc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 06:45:13 by shutan            #+#    #+#             */
/*   Updated: 2025/09/05 08:14:55 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

static int	calculate_tex_x_with_flip(t_flip_params *params)
{
	int	tex_x;

	tex_x = (int)(params->wall_x * (double)params->texture->width);
	if ((params->wall_side == 0 && params->ray_dir_x < 0)
		|| (params->wall_side == 1 && params->ray_dir_y < 0))
		tex_x = params->texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= params->texture->width)
		tex_x = params->texture->width - 1;
	return (tex_x);
}

int	calculate_texture_x_with_flip(t_flip_params *params)
{
	return (calculate_tex_x_with_flip(params));
}
