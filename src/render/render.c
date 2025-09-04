/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:23:08 by shutan            #+#    #+#             */
/*   Updated: 2025/09/04 18:58:11 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Initialize rendering system */
int	init_rendering(t_game *game)
{
	if (!init_screen_image(game))
	{
		ft_printf("Error: Failed to initialize screen image\n");
		return (0);
	}
	if (!load_textures(game))
	{
		ft_printf("Error: Failed to load textures\n");
		return (0);
	}
	return (1);
}

/* Main rendering function called each frame */
int	render_frame(t_game *game)
{
	update_movement(game);
	draw_floor_ceiling(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
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
