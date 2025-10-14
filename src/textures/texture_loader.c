/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalizon <ggalizon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 02:00:00 by shutan            #+#    #+#             */
/*   Updated: 2025/10/13 11:54:05 by ggalizon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Check if texture file exists and is readable */
static int	validate_texture_file(char *path)
{
	int		fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

/* Load a single texture from XPM file */
void	load_texture(t_game *game, t_img *texture, char *path)
{
	if (!path)
		error_exit(ERR_MISSING_CONFIG, game, "texture path");
	if (!validate_texture_file(path))
		error_exit(ERR_XPM_LOAD, game, path);
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		error_exit(ERR_XPM_LOAD, game, path);
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (!texture->addr)
	{
		mlx_destroy_image(game->mlx, texture->img);
		error_exit(ERR_IMG_DATA_ADDR, game, NULL);
	}
}

/* Load all textures for the game */
void	load_all_textures(t_game *game)
{
	if (game->textures->loaded)
		return ;
	if (!validate_texture_file(game->textures->no))
		error_exit(ERR_XPM_LOAD, game, game->textures->no);
	if (!validate_texture_file(game->textures->so))
		error_exit(ERR_XPM_LOAD, game, game->textures->so);
	if (!validate_texture_file(game->textures->we))
		error_exit(ERR_XPM_LOAD, game, game->textures->we);
	if (!validate_texture_file(game->textures->ea))
		error_exit(ERR_XPM_LOAD, game, game->textures->ea);
	load_texture(game, &game->textures->imgs[0], game->textures->no);
	load_texture(game, &game->textures->imgs[1], game->textures->so);
	load_texture(game, &game->textures->imgs[2], game->textures->we);
	load_texture(game, &game->textures->imgs[3], game->textures->ea);
	game->textures->loaded = 1;
}

/* Load all textures from file paths */
static void	load_single_texture(t_game *game, int index, char *path)
{
	int	width;
	int	height;

	if (!validate_texture_file(path))
		error_exit(ERR_XPM_LOAD, game, path);
	game->textures->imgs[index].img = mlx_xpm_file_to_image(game->mlx,
			path, &width, &height);
	if (!game->textures->imgs[index].img)
		error_exit(ERR_XPM_LOAD, game, path);
	game->textures->imgs[index].width = width;
	game->textures->imgs[index].height = height;
	game->textures->imgs[index].addr = mlx_get_data_addr(
			game->textures->imgs[index].img,
			&game->textures->imgs[index].bits_per_pixel,
			&game->textures->imgs[index].line_length,
			&game->textures->imgs[index].endian);
}

void	load_textures(t_game *game)
{
	if (!game->textures->no || !game->textures->so
		|| !game->textures->we || !game->textures->ea)
	{
		error_exit(ERR_MISSING_CONFIG, game, "texture paths");
	}
	load_single_texture(game, 0, game->textures->no);
	load_single_texture(game, 1, game->textures->so);
	load_single_texture(game, 2, game->textures->we);
	load_single_texture(game, 3, game->textures->ea);
	game->textures->loaded = 1;
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
