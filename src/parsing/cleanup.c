#include "../../include/cub3d.h"

#include "../../include/cub3d.h"


void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	cleanup_parsing(t_game *game)
{
	if (!game)
		return;
	if (game->map)
	{
		if (game->map->arr)
			free_arr(game->map->arr);
		free(game->map);
	}
	if (game->textures)
	{
		if (game->textures->NO)
			free(game->textures->NO);
		if (game->textures->SO)
			free(game->textures->SO);
		if (game->textures->WE)
			free(game->textures->WE);
		if (game->textures->EA)
			free(game->textures->EA);
		free(game->textures);
	}
	if (game->player)
		free(game->player);
}
