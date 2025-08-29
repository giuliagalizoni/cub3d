#include "../../include/cub3d.h"

static int is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'W' || c == 'E');
}
int	scan_map(t_map *map)
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
			{
				ft_printf("Error: Invalid character '%c' in map\n", map->arr[y][x]);
				//cleanup
				return (0);
			}
			if (map->arr[y][x] == 'N' || map->arr[y][x] == 'S'
				|| map->arr[y][x] == 'W'|| map->arr[y][x] == 'E')
			{
				if (map->player_dir)
				{
					//cleanup
					ft_printf("Error: duplicated player position");
					return (0);
				}
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
	{
		ft_printf("Error: player position is missing");
		//cleanup
		return (0);
	}
	return (1);
}
