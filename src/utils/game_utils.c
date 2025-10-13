/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalizon <ggalizon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:54:29 by ggalizon          #+#    #+#             */
/*   Updated: 2025/10/13 13:56:20 by ggalizon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->minimap.img && game->mlx)
		mlx_destroy_image(game->mlx, game->minimap.img);
	if (game->textures && game->textures->loaded)
		free_textures(game);
	if (game->screen.img && game->mlx)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

static void	print_texture_info(t_game game)
{
	ft_printf("NO: %s\n", game.textures->no);
	ft_printf("SO: %s\n", game.textures->so);
	ft_printf("WE: %s\n", game.textures->we);
	ft_printf("EA: %s\n", game.textures->ea);
	ft_printf("F: %d\n", game.textures->f);
	ft_printf("C: %d\n", game.textures->c);
}

static void	print_map_info(t_game game)
{
	int	i;

	ft_printf("\n## MAP ARR##\n");
	i = 0;
	while (game.map->arr[i])
	{
		ft_printf("%s\n", game.map->arr[i]);
		i++;
	}
	ft_printf("\n");
	ft_printf("map height: %d\n", game.map->height);
	ft_printf("map width: %d\n", game.map->width);
	ft_printf("player position x: %d\n", game.map->player_x);
	ft_printf("player position y: %d\n", game.map->player_y);
	ft_printf("player direction: %c\n", game.map->player_dir);
}

void	debug_prints(t_game game)
{
	print_texture_info(game);
	print_map_info(game);
}

void	setup_game(t_game *game)
{
	game->floor_color = mlx_get_color_value(game->mlx, game->textures->f);
	game->ceiling_color = mlx_get_color_value(game->mlx, game->textures->c);
	load_all_textures(game);
	init_screen_image(game);
}
