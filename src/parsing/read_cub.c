#include "../../include/cub3d.h"

int	is_equal(char *str1, char *str2)
{
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	if (!ft_strncmp(str1, str2, ft_strlen(str2)))
		return (1);
	return (0);
}

static void	set_texture(char **field, char *path, char *id)
{
	if (*field)
	{
		ft_printf("Error: Duplicate texture identifier for %s\n", id);
		exit(1); //TODO: cleanup;
	}
	*field = ft_strdup(path);
}

static int	parse_rgb(char *rgb_str)
{
	int	r;
	int	g;
	int	b;
	char **rgb_arr;

	rgb_arr = ft_split(rgb_str, ',');
	if (!rgb_arr)
		return (-1); // handle error and exit
	r = atoi(rgb_arr[0]);
	g = atoi(rgb_arr[1]);
	b = atoi(rgb_arr[2]);
	return ((r << 16) | (g << 8) | b);
}

static void	set_rgb(int *field, char *rgb_str, char *id)
{
	if (*field != -1)
		{
			ft_printf("Error: Duplicate identifier for %s\n", id);
			exit(1); //TODO: cleanup;
		}
	*field = parse_rgb(rgb_str);
}

static void	parse_line(char *line, t_game *game)
{
	char	*trimmed;
	char **tokens;

	trimmed = ft_strtrim(line, " \t\n\v\f\r");
		if (!trimmed || !(*trimmed))
			return;

	tokens = ft_split(trimmed, ' '); // TODO: REDO THIS LOGIC
		if (!tokens || !tokens[0] || !tokens[1])
			return ; // handle error free trimmed

	if (is_equal(tokens[0], "NO"))
		set_texture(&game->textures->NO, tokens[1], "NO");
	else if (is_equal(tokens[0], "SO"))
		set_texture(&game->textures->SO, tokens[1], "SO");
	else if (is_equal(tokens[0], "WE"))
		set_texture(&game->textures->WE, tokens[1], "WE");
	else if (is_equal(tokens[0], "EA"))
		set_texture(&game->textures->EA, tokens[1], "EA");
	else if (is_equal(tokens[0], "F"))
		set_rgb(&game->textures->F, tokens[1], "F");
	else if (is_equal(tokens[0], "C"))
		set_rgb(&game->textures->C, tokens[1], "C");
	else
	{
		if (!game->textures->NO || !game->textures->SO || !game->textures->WE
			|| !game->textures->EA || !game->textures->F || !game->textures->C)
			return; // error missing config
		parse_map(line, game);
	}
	// TODO: free tokens arr
	free(trimmed);
}

void	read_cub(char *path, t_game *game)
{
	int		fd;
	char	*line;
	// char	*trimmed;
	// char **tokens;

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
		// trimmed = ft_strtrim(line, " \t\n\v\f\r");
		// free(line);
		// if (!trimmed || !(*trimmed))
		// 	break;

		// tokens = ft_split(trimmed, ' '); // do I have to consider other spaces?
		// if (!tokens || !tokens[0] || !tokens[1])
		// 	return ; // handle error free trimmed

		parse_line(line, game);

		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
