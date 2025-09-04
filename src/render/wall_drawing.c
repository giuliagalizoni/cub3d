/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 06:48:28 by shutan            #+#    #+#             */
/*   Updated: 2025/09/04 16:18:54 by shutan           ###   ########.fr       */
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

/* Draw a textured vertical wall slice */
void	draw_wall_slice_textured(t_game *game, int x, double wall_height, int wall_side, double ray_angle, double wall_x)
{
	int		start_y;
	int		end_y;
	int		y;
	t_img	*texture;
	int		tex_x;
	int		tex_y;
	int		color;

	start_y = (WIN_HEIGHT - wall_height) / 2;
	end_y = (WIN_HEIGHT + wall_height) / 2;
	if (start_y < 0)
		start_y = 0;
	if (end_y >= WIN_HEIGHT)
		end_y = WIN_HEIGHT - 1;
	texture = get_wall_texture_advanced(game, wall_side, ray_angle);
	if (!texture || !texture->img)
	{
		draw_wall_slice(game, x, wall_height);
		return;
	}
	tex_x = calculate_texture_x(texture, wall_x);
	y = start_y;
	while (y <= end_y)
	{
		tex_y = calculate_texture_y(texture, y, start_y, wall_height);
		color = get_texture_pixel(texture, tex_x, tex_y);
		put_pixel(&game->screen, x, y, color);
		y++;
	}
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

/* Initialize player position and direction */
void	init_player(t_game *game, double x, double y, char direction)
{
	game->player->x = x + 0.5;
	game->player->y = y + 0.5;
	if (direction == 'N')
		game->player->angle = 3 * PI / 2;
	else if (direction == 'S')
		game->player->angle = PI / 2;
	else if (direction == 'E')
		game->player->angle = 0;
	else if (direction == 'W')
		game->player->angle = PI;
	game->player->dx = cos(game->player->angle);
	game->player->dy = sin(game->player->angle);
}

/* Set default floor and ceiling colors */
void	set_default_colors(t_game *game)
{
	game->floor_color = 0x654321;
	game->ceiling_color = 0x87CEEB;
}
