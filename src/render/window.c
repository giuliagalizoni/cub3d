/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:22:55 by shutan            #+#    #+#             */
/*   Updated: 2025/08/29 08:45:14 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Initialize MLX and create window */
int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (0);
	return (1);
}

/* Initialize screen image buffer */
int	init_screen_image(t_game *game)
{
	game->screen.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->screen.img)
		return (0);
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bits_per_pixel,
			&game->screen.line_length,
			&game->screen.endian);
	return (1);
}

/* Set up event hooks */
void	setup_hooks(t_game *game)
{
#ifdef __linux__
	/* Linux: Use mlx_hook for key events */
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game); /* KeyPress */
	mlx_hook(game->win, 3, 1L << 1, handle_keyrelease, game); /* KeyRelease */
	mlx_hook(game->win, 17, 0, close_window, game); /* ClientMessage for close */
#else
	/* macOS: Use mlx_hook for key events */
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game); /* KeyPress */
	mlx_hook(game->win, 3, 1L << 1, handle_keyrelease, game); /* KeyRelease */
	mlx_hook(game->win, RED_CROSS, 0, close_window, game);
#endif
	mlx_loop_hook(game->mlx, render_frame, game);
}

/* Close window and exit program */
int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

/* Clean up all allocated resources */
void	cleanup_game(t_game *game)
{
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
}
