#include "../../include/cub3d.h"

static int	check_ext(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len <= 4)
		return (0);
	if (!ft_strnstr(path, ".cub", len))
		return (0);
	if (path[len - 4] != '.')
		return (0);
	if (path[len - 3] != 'c')
		return (0);
	if (path[len - 2] != 'u')
		return (0);
	if (path[len - 1] != 'b')
		return (0);
	return (1);
}

void	parser(char *path, t_game *game)
{
	if (!check_ext(path))
		error_exit(ERR_FILE_EXT, game, path);
	read_cub(path, game);
	validade_map(game);
}
