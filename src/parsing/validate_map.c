#include "../../include/cub3d.h"

char	**copy_arr(char **arr, int size, t_game *game)
{
	char	**new_arr;
	int		i;

	if (!arr)
		return (NULL);
	new_arr = malloc((size + 1) * sizeof(char *));
	if (!new_arr)
		error_exit(ERR_MALLOC, game, "copy_arr");
	i = 0;
	while (i < size)
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
			error_exit(ERR_MALLOC, game, "copy_arr");
		i++;
	}
	new_arr[size] = NULL;
	return (new_arr);
}

int	flood_fill(char **map_copy, int x, int y, t_map *map)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (0);
	if (map_copy[y][x] == ' ')
		return (0);
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'V')
		return (1);
	map_copy[y][x] = 'V';
	if (!flood_fill(map_copy, x + 1, y, map))
		return (0);
	if (!flood_fill(map_copy, x - 1, y, map))
		return (0);
	if (!flood_fill(map_copy, x, y + 1, map))
		return (0);
	if (!flood_fill(map_copy, x, y - 1, map))
		return (0);
	return (1);
}

void	validade_map(t_game *game)
{
	char	**map_copy;
	t_map	*map;

	map = game->map;
	scan_map(map, game);
	map_copy = copy_arr(map->arr, map->height, game);
	if (!flood_fill(map_copy, map->player_x,
			map->player_y, map))
	{
		free_arr(map_copy);
		error_exit(ERR_MAP_NOT_CLOSED, game, NULL);
	}
	free_arr(map_copy);
}
