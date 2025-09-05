/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 06:48:28 by shutan            #+#    #+#             */
/*   Updated: 2025/09/05 05:43:27 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Draw a vertical wall slice */
void	draw_wall_slice(t_game *game, int x, double wall_height)
{
	int	start_y;
	int	end_y;
	int	y;
	int	color;

	start_y = (WIN_HEIGHT - wall_height) / 2;
	end_y = (WIN_HEIGHT + wall_height) / 2;
	if (start_y < 0)
		start_y = 0;
	if (end_y >= WIN_HEIGHT)
		end_y = WIN_HEIGHT - 1;
	color = 0xFFFFFF;
	y = start_y;
	while (y <= end_y)
	{
		put_pixel(&game->screen, x, y, color);
		y++;
	}
}

static void	draw_texture_column(t_game *game, int x, t_texture_draw *draw_data)
{
	int		y;
	int		tex_y;
	int		color;

	y = draw_data->start_y;
	while (y <= draw_data->end_y)
	{
		tex_y = (int)draw_data->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= draw_data->texture->height)
			tex_y = draw_data->texture->height - 1;
		draw_data->tex_pos += draw_data->tex_step;
		color = get_texture_pixel(draw_data->texture, draw_data->tex_x, tex_y);
		put_pixel(&game->screen, x, y, color);
		y++;
	}
}

void	draw_wall_slice_textured(t_game *game, int x, double wall_height,
		t_ray_data *ray_data)
{
	t_texture_draw	draw_data;

	draw_data.start_y = (WIN_HEIGHT - wall_height) / 2;
	draw_data.end_y = (WIN_HEIGHT + wall_height) / 2;
	if (draw_data.start_y < 0)
		draw_data.start_y = 0;
	if (draw_data.end_y >= WIN_HEIGHT)
		draw_data.end_y = WIN_HEIGHT - 1;
	draw_data.texture = get_wall_texture_by_direction(game, ray_data->wall_side,
			ray_data->ray_dir_x, ray_data->ray_dir_y);
	if (!draw_data.texture || !draw_data.texture->img)
	{
		draw_wall_slice(game, x, wall_height);
		return ;
	}
	draw_data.tex_x = calculate_texture_x_with_flip(draw_data.texture,
			ray_data->wall_x, ray_data->wall_side, ray_data->ray_dir_x,
			ray_data->ray_dir_y);
	draw_data.tex_step = (double)draw_data.texture->height / wall_height;
	draw_data.tex_pos = (draw_data.start_y - WIN_HEIGHT / 2.0 + wall_height
			/ 2.0) * draw_data.tex_step;
	draw_texture_column(game, x, &draw_data);
}

/* Check if coordinate is a wall */
int	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map->width)
		return (1);
	if (y < 0 || y >= game->map->height)
		return (1);
	if (game->map->arr[y][x] == '1')
		return (1);
	return (0);
}

/* Set default floor and ceiling colors */
void	set_default_colors(t_game *game)
{
	game->floor_color = 0x8B4513;
	game->ceiling_color = 0x87CEEB;
}
