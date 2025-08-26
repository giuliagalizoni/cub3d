#include "../../include/cub3d.h"

static char	**push_to_arr(char **arr, int size, char *line)
{
	char	**new_arr;
	int		i;

	new_arr = malloc(sizeof(char *) * size + 2);
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[size] = ft_strdup(line);
	new_arr[size + 1] = NULL;
	free(arr);
	return (new_arr);
}

void	parse_map(int fd, char *first_line, t_game *game)
{
	char	*line;
	int		size;

	size = 0;
	game->map->arr = push_to_arr(game->map->arr, size++, first_line);
	if (!game->map->arr)
	{
		perror("malloc"); // TODO: wrapper function
		exit(EXIT_FAILURE);
	}

	line = get_next_line(fd);
	while (line)
	{
		game->map->arr = push_to_arr(game->map->arr, size++, line);
		if (!game->map->arr)
		{
			perror("malloc"); // TODO: wrapper function
			exit(EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}

}
