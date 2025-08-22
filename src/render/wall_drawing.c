/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 06:48:28 by shutan            #+#    #+#             */
/*   Updated: 2025/08/22 06:48:30 by shutan           ###   ########.fr       */
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

/* Check if coordinate is a wall */
int	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width)
		return (1);
	if (y < 0 || y >= game->map_height)
		return (1);
	if (game->map[y][x] == '1')
		return (1);
	return (0);
}

/* Initialize player position and direction */
void	init_player(t_game *game, double x, double y, char direction)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	if (direction == 'N')
		game->player.angle = 3 * PI / 2;
	else if (direction == 'S')
		game->player.angle = PI / 2;
	else if (direction == 'E')
		game->player.angle = 0;
	else if (direction == 'W')
		game->player.angle = PI;
	game->player.dx = cos(game->player.angle);
	game->player.dy = sin(game->player.angle);
}

/* Set default floor and ceiling colors */
void	set_default_colors(t_game *game)
{
	game->floor_color = 0x654321;
	game->ceiling_color = 0x87CEEB;
}
