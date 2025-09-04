/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 02:00:00 by shutan            #+#    #+#             */
/*   Updated: 2025/09/04 18:59:44 by shutan           ###   ########.fr       */
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

/* Load all textures from file paths */
int	load_textures(t_game *game)
{
	int	width;
	int	height;

	if (!game->textures->NO || !game->textures->SO || 
		!game->textures->WE || !game->textures->EA)
	{
		ft_printf("Error: Missing texture paths\n");
		return (0);
	}
	
	// Load North texture
	game->textures->imgs[0].img = mlx_xpm_file_to_image(game->mlx,
			game->textures->NO, &width, &height);
	if (!game->textures->imgs[0].img)
	{
		ft_printf("Error: Failed to load North texture: %s\n", game->textures->NO);
		return (0);
	}
	game->textures->imgs[0].width = width;
	game->textures->imgs[0].height = height;
	game->textures->imgs[0].addr = mlx_get_data_addr(game->textures->imgs[0].img,
			&game->textures->imgs[0].bits_per_pixel,
			&game->textures->imgs[0].line_length,
			&game->textures->imgs[0].endian);
	
	// Load South texture
	game->textures->imgs[1].img = mlx_xpm_file_to_image(game->mlx,
			game->textures->SO, &width, &height);
	if (!game->textures->imgs[1].img)
	{
		ft_printf("Error: Failed to load South texture: %s\n", game->textures->SO);
		free_textures(game);
		return (0);
	}
	game->textures->imgs[1].width = width;
	game->textures->imgs[1].height = height;
	game->textures->imgs[1].addr = mlx_get_data_addr(game->textures->imgs[1].img,
			&game->textures->imgs[1].bits_per_pixel,
			&game->textures->imgs[1].line_length,
			&game->textures->imgs[1].endian);
	
	// Load West texture
	game->textures->imgs[2].img = mlx_xpm_file_to_image(game->mlx,
			game->textures->WE, &width, &height);
	if (!game->textures->imgs[2].img)
	{
		ft_printf("Error: Failed to load West texture: %s\n", game->textures->WE);
		free_textures(game);
		return (0);
	}
	game->textures->imgs[2].width = width;
	game->textures->imgs[2].height = height;
	game->textures->imgs[2].addr = mlx_get_data_addr(game->textures->imgs[2].img,
			&game->textures->imgs[2].bits_per_pixel,
			&game->textures->imgs[2].line_length,
			&game->textures->imgs[2].endian);
	
	// Load East texture
	game->textures->imgs[3].img = mlx_xpm_file_to_image(game->mlx,
			game->textures->EA, &width, &height);
	if (!game->textures->imgs[3].img)
	{
		ft_printf("Error: Failed to load East texture: %s\n", game->textures->EA);
		free_textures(game);
		return (0);
	}
	game->textures->imgs[3].width = width;
	game->textures->imgs[3].height = height;
	game->textures->imgs[3].addr = mlx_get_data_addr(game->textures->imgs[3].img,
			&game->textures->imgs[3].bits_per_pixel,
			&game->textures->imgs[3].line_length,
			&game->textures->imgs[3].endian);
	
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
