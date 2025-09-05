/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 02:00:00 by shutan            #+#    #+#             */
/*   Updated: 2025/09/05 06:12:48 by shutan           ###   ########.fr       */
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
	if (!load_texture(game, &game->textures->imgs[0], game->textures->no))
		return (0);
	if (!load_texture(game, &game->textures->imgs[1], game->textures->so))
		return (0);
	if (!load_texture(game, &game->textures->imgs[2], game->textures->we))
		return (0);
	if (!load_texture(game, &game->textures->imgs[3], game->textures->ea))
		return (0);
	game->textures->loaded = 1;
	return (1);
}

/* Load all textures from file paths */
static int	load_single_texture(t_game *game, int index, char *path)
{
	int	width;
	int	height;

	game->textures->imgs[index].img = mlx_xpm_file_to_image(game->mlx,
			path, &width, &height);
	if (!game->textures->imgs[index].img)
	{
		ft_printf("Error: Failed to load texture: %s\n", path);
		return (0);
	}
	game->textures->imgs[index].width = width;
	game->textures->imgs[index].height = height;
	game->textures->imgs[index].addr = mlx_get_data_addr(
			game->textures->imgs[index].img,
			&game->textures->imgs[index].bits_per_pixel,
			&game->textures->imgs[index].line_length,
			&game->textures->imgs[index].endian);
	return (1);
}

int	load_textures(t_game *game)
{
	if (!game->textures->no || !game->textures->so
		|| !game->textures->we || !game->textures->ea)
	{
		ft_printf("Error: Missing texture paths\n");
		return (0);
	}
	if (!load_single_texture(game, 0, game->textures->no))
		return (0);
	if (!load_single_texture(game, 1, game->textures->so))
	{
		free_textures(game);
		return (0);
	}
	if (!load_single_texture(game, 2, game->textures->we))
	{
		free_textures(game);
		return (0);
	}
	if (!load_single_texture(game, 3, game->textures->ea))
	{
		free_textures(game);
		return (0);
	}
	game->textures->loaded = 1;
	return (1);
}

/* Free all loaded textures */
void	free_textures(t_game *game)
{
	int	i;

	if (!game->textures || !game->textures->loaded)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->textures->imgs[i].img)
			mlx_destroy_image(game->mlx, game->textures->imgs[i].img);
		i++;
	}
	game->textures->loaded = 0;
}
