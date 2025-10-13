/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalizon <ggalizon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:23:08 by shutan            #+#    #+#             */
/*   Updated: 2025/09/25 15:26:20 by ggalizon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Initialize rendering system */
void	init_rendering(t_game *game)
{
	init_screen_image(game);
	load_textures(game);
}

/* Main rendering function called each frame */
int	render_frame(t_game *game)
{
	int	pad;
	int	x;
	int	y;

	update_movement(game);
	draw_floor_ceiling(game);
	cast_rays(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	pad = 100;
	x = WIN_WIDTH - game->minimap.width - pad;
	y = WIN_HEIGHT - game->minimap.height - pad;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, x, y);
	return (0);
}

/* Clear entire image with specified color */
void	clear_image(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

/* Put a pixel at specified coordinates */
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x
				* (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

/* Draw floor and ceiling with their respective colors */
void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(&game->screen, x, y, game->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(&game->screen, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}
