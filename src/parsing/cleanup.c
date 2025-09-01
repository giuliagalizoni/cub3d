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

void	exhaust_gnl(int fd)
{
	char	*temp;

	if (fd < 0)
		return;
	temp = get_next_line(fd);
	while (temp)
	{
		free(temp);
		temp = get_next_line(fd);
	}
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

void	ft_perror(char *err_message)
{
	write(2, "Error: ", 7);
	write(2, err_message, ft_strlen(err_message));
	write(2, "\n", 1);
}
