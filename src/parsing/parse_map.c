#include "../../include/cub3d.h"

static char	**push_to_arr(char **arr, int size, char *line)
{
	char	**new_arr;
	int		i;
	char	*trimmed;

	new_arr = malloc(sizeof(char *) * (size + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_arr[i] = arr[i];
		i++;
	}
	trimmed = ft_strtrun(line, "\n");
	if (!trimmed)
	{
		// free(new_arr); TODO
		return (NULL);
	}
	new_arr[size] = trimmed;
	new_arr[size + 1] = NULL;
	if (arr)
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
		if (line[0] == '\n') // Skip empty lines after the map starts
		{
			ft_printf("Error: Empty line inside map definition.\n");
			free(line);
			// cleanup
			exit(EXIT_FAILURE);
		}
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
