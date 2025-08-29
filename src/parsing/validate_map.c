#include "../../include/cub3d.h"

/*TODO validate:
- walls
- blank spaces
- invalid chars
*/

int	check_walls(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || ft_strchr("NSEW", map[i][j]))
			{
				 if (!map[i - 1] || !map[i + 1] ||
					j >= (int)ft_strlen(map[i - 1]) ||
					j >= (int)ft_strlen(map[i + 1]) ||
					map[i - 1][j] == ' ' || map[i + 1][j] == ' ' ||
					map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	validade_map(t_map *map)
{
	if (!scan_map(map))
		exit(EXIT_FAILURE); //cleanup
	if (!check_walls(map->arr))
	{
		ft_printf("There's a whole in the map :(\n");
		// cleanup
		exit(EXIT_FAILURE);
	}
}
