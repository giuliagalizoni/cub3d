#include "../../include/cub3d.h"

static int is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'W' || c == 'E');
}
void	scan_map(t_map *map, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (map->arr[y])
	{
		x = 0;
		while (map->arr[y][x])
		{
			if (!is_valid_char(map->arr[y][x]))
				error_exit(ERR_INVALID_CHAR_MAP, game, NULL);
			if (map->arr[y][x] == 'N' || map->arr[y][x] == 'S'
				|| map->arr[y][x] == 'W'|| map->arr[y][x] == 'E')
			{
				if (map->player_dir)
					error_exit(ERR_DUPLICATE_PLAYER, game, NULL);
				map->player_dir = map->arr[y][x];
				map->player_x = x;
				map->player_y = y;
				map->arr[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	if (!map->player_dir || map->player_x == -1 || map->player_y == -1)
		error_exit(ERR_MISSING_PLAYER, game, NULL);
}
