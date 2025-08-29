#include "../../include/cub3d.h"

char **copy_arr(char **arr, int size)
{
	char	**new_arr;
	int		i;

	if (!arr)
		return (NULL);
	new_arr = malloc((size + 1) * sizeof(char *));
	if (!new_arr)
	{
		perror("Malloc error in copy_arr");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < size)
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
		{
			perror("ft_strdup error in copy_arr");
			free_arr(new_arr);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	new_arr[size] = NULL;
	return (new_arr);
}

int	flood_fill(char **map, int x, int y, int height, int width)
{
	if (y < 0 || y >= height || x < 0 || x >= width)
		return (0);
	if (map[y][x] == ' ')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (1);
	map[y][x] = 'V';
	if (!flood_fill(map, x + 1, y, height, width))
		return (0);
	if (!flood_fill(map, x - 1, y, height, width))
		return (0);
	if (!flood_fill(map, x, y + 1, height, width))
		return (0);
	if (!flood_fill(map, x, y - 1, height, width))
		return (0);
	return (1);
}

void	validade_map(t_game *game)
{
	char	**map_copy;
	t_map	*map;

	map = game->map;
	if (!scan_map(map))
	{
		ft_printf("Error: Invalid map content or player definition.\n");
		cleanup_parsing(game);
		exit(EXIT_FAILURE);
	}
	map_copy = copy_arr(map->arr, map->height);
	if (!flood_fill(map_copy, map->player_x, map->player_y, map->height, map->width))
	{
		ft_printf("There's a whole in the map :(\n");
		free_arr(map_copy);
		cleanup_parsing(game);
		exit(EXIT_FAILURE);
	}
	free_arr(map_copy);
}
