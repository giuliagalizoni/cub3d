/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalizon <ggalizon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:22:55 by shutan            #+#    #+#             */
/*   Updated: 2025/09/25 15:36:03 by ggalizon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Initialize MLX and create window */
void	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		error_exit(ERR_MLX_INIT, game, NULL);
	}
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
	{
		error_exit(ERR_WIN_CREATE, game, NULL);
	}
}

/* Initialize screen image buffer */
void	init_screen_image(t_game *game)
{
	game->screen.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->screen.img)
		error_exit(ERR_IMG_CREATE, game, NULL);
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bits_per_pixel,
			&game->screen.line_length,
			&game->screen.endian);
	if (!game->screen.addr)
		error_exit(ERR_IMG_DATA_ADDR, game, NULL);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->win, RED_CROSS, 0, close_window, game);
	mlx_loop_hook(game->mlx, render_frame, game);
}

/* Close window and exit program */
int	close_window(t_game *game)
{
	cleanup_parsing(game);
	cleanup_game(game);
	exit(0);
	return (0);
}
