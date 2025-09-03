#include "../../include/cub3d.h"

static int	is_config_all_set(t_game *game)
{
	if (game->textures->NO && game->textures->SO
		&& game->textures->WE && game->textures->EA
		&& game->textures->F != -1 && game->textures->C != -1)
		return (1);
	return (0);
}

static char	*read_config(int fd, t_game *game)
{
	char	*line;
	int		result;

	line = get_next_line(fd);
	while(line)
	{
		result = parse_config_line(line, game);
		if (result == -1)
			return (line);
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

void	read_cub(char *path, t_game *game)
{
	int		fd;
	char	*map_start;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit(ERR_FILE_OPEN, game, path);
	map_start = read_config(fd, game);
	if (!is_config_all_set(game))
	{
		if (map_start)
			free(map_start);
		exhaust_gnl(fd);
		error_exit(ERR_MISSING_CONFIG, game, NULL);
	}
	if (!map_start)
	{
		close(fd);
		error_exit(ERR_MISSING_MAP, game, NULL);
	}
	parse_map(fd, map_start, game);
	free(map_start);
	close(fd);
}
