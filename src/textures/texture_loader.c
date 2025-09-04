/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 02:00:00 by shutan            #+#    #+#             */
/*   Updated: 2025/09/04 02:22:32 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Load a single texture from XPM file */
int	load_texture(t_game *game, t_img *texture, char *path)
{
	if (!path)
		return (0);
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		ft_printf("Error: Failed to load texture: %s\n", path);
		return (0);
	}
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (!texture->addr)
	{
		mlx_destroy_image(game->mlx, texture->img);
		return (0);
	}
	return (1);
}

/* Load all textures for the game */
int	load_all_textures(t_game *game)
{
	if (game->textures->loaded)
		return (1);
	if (!load_texture(game, &game->textures->imgs[0], game->textures->NO))
		return (0);
	if (!load_texture(game, &game->textures->imgs[1], game->textures->SO))
		return (0);
	if (!load_texture(game, &game->textures->imgs[2], game->textures->WE))
		return (0);
	if (!load_texture(game, &game->textures->imgs[3], game->textures->EA))
		return (0);
	game->textures->loaded = 1;
	return (1);
}

/* Free all loaded textures */
void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures->imgs[i].img)
			mlx_destroy_image(game->mlx, game->textures->imgs[i].img);
		i++;
	}
}