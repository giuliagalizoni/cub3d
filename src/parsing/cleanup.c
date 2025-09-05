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

void	cleanup_parsing(t_game *game)
{
	if (!game)
		return ;

	if (game->map)
	{
		if (game->map->arr)
			free_arr(game->map->arr);
		free(game->map);
	}
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
	}
	if (game->player)
		free(game->player);
}
