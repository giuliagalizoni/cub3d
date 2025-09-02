#include "../../include/cub3d.h"

void	get_dimensions(t_map *map)
{
	char **arr = map->arr;
	int	y;
	int	x;
	int	width;

	y = 0;
	width = 0;
	while (arr[y])
	{
		x = ft_strlen(arr[y]);
		if (x > width)
			width = x;
		y++;
	}
	map->height = y;
	map->width = width;
}

static void	pad_map(t_game *game)
{
	int		i;
	int		len;
	char	*new_row;

	i = 0;
	while (game->map->arr[i])
	{
		len = ft_strlen(game->map->arr[i]);
		if (len < game->map->width)
		{
			new_row = malloc(game->map->width + 1);
			if (!new_row)
				error_exit(ERR_MALLOC, game);
			ft_memcpy(new_row, game->map->arr[i], len);
			ft_memset(new_row + len, ' ', game->map->width - len);
			new_row[game->map->width] = '\0';
			free(game->map->arr[i]);
			game->map->arr[i] = new_row;
		}
		i++;
	}
}
static char	**push_to_arr(char **arr, int size, char *line)
{
	char	**new_arr;
	int		i;

	new_arr = malloc(sizeof(char *) * (size + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[size] = ft_strtrim(line, "\n");
	if (!new_arr[size])
	{
		free_arr(new_arr);
		return NULL;
	}
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
		error_exit(ERR_MALLOC, game);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(first_line);
			free(line);
			exhaust_gnl(fd);
			error_exit(ERR_EMPTY_LINE_MAP, game);
		}
		game->map->arr = push_to_arr(game->map->arr, size++, line);
		if (!game->map->arr)
			error_exit(ERR_MALLOC, game);
		free(line);
		line = get_next_line(fd);
	}
	get_dimensions(game->map);
	pad_map(game);
}
