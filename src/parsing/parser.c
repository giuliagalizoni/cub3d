#include "../../includes/cub3d.h"

int	is_equal(char *str1, char *str2)
{
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	if (!ft_strncmp(str1, str2, ft_strlen(str2)))
		return (1);
	return (0);
}

void	read_cub(char *path, t_game *game)
{
	int		fd;
	char	*line;
	char	*trimmed;
	char **tokens;

	fd = open(path, O_RDONLY);
	ft_printf("path: %s\n", path);
	if (fd < 0)
	{
		perror("Error opening file");
		return ; // handle error
	}
	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\n\v\f\r");
		free(line);
		if (!trimmed || !(*trimmed))
			break;
		tokens = ft_split(trimmed, ' '); // do I have to consider other spaces?
		if (!tokens || !tokens[0] || !tokens[1])
			return ; // handle error free trimmed
		if (is_equal(tokens[0], "NO"))
			game->textures->NO = ft_strdup(tokens[1]);
		else if (is_equal(tokens[0], "SO"))
			game->textures->SO = ft_strdup(tokens[1]);
		else if (is_equal(tokens[0], "WE"))
			game->textures->WE = ft_strdup(tokens[1]);
		else if (is_equal(tokens[0], "EA"))
			game->textures->EA = ft_strdup(tokens[1]);
		else if (is_equal(tokens[0], "F"))
			ft_printf("F: %s\n", tokens[1]); // TODO: decide how to store
		else if (is_equal(tokens[0], "C"))
			ft_printf("C: %s\n", tokens[1]); // TODO
		else
		{
			ft_printf("Error parsing");
			return ; // check map starting
		}

		// TODO: free tokens arr

		free(trimmed);
		line = get_next_line(fd);
	}
	close(fd);
}

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
	{
		ft_printf("Wrong extension\n");
		return ; // figure out exit and error printing
	}
	read_cub(path, game);



}

