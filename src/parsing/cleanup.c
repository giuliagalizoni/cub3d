/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalizon <ggalizon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:48:54 by ggalizon          #+#    #+#             */
/*   Updated: 2025/10/13 14:28:33 by ggalizon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	exhaust_gnl(int fd)
{
	char	*temp;

	if (fd < 0)
		return ;
	temp = get_next_line(fd);
	while (temp)
	{
		free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
}

static void	cleanup_textures(t_game *game)
{
	if (game->textures)
	{
		if (game->textures->no)
			free(game->textures->no);
		if (game->textures->so)
			free(game->textures->so);
		if (game->textures->we)
			free(game->textures->we);
		if (game->textures->ea)
			free(game->textures->ea);
		free(game->textures);
		game->textures = NULL;
	}
}

void	cleanup_parsing(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
	{
		if (game->map->arr)
		{
			free_arr(game->map->arr);
			game->map->arr = NULL;
		}
		free(game->map);
		game->map = NULL;
	}
	cleanup_textures(game);
	if (game->player)
	{
		free(game->player);
		game->player = NULL;
	}
}
