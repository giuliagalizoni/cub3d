/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 06:40:41 by shutan            #+#    #+#             */
/*   Updated: 2025/09/05 06:45:13 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	print_textures(t_game game)
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
	print_textures(game);
	print_map_info(game);
}
