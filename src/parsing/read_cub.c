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

char	*get_first_word(char *line)
{
	int i;
	int start;
	int end;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t') // do I need this, since I have trimmed the line first? maybe it's better to do it only here;
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	end = i;
	return (ft_substr(line, start, end - start));
}

static int	parse_config_line(char *line, t_game *game)
{
	char	*trimmed;
	char	*id;
	char	*value;

	trimmed = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed)
		return (0);
	if (!*trimmed)
	{
		free(trimmed);
		return (0);
	}
	id = get_first_word(trimmed);
	value = trimmed + ft_strlen(id);
	while (*value == ' ' || *value == '\t')
		value++;
	if (is_equal(id, "NO"))
		set_texture(&game->textures->NO, value, "NO");
	else if (is_equal(id, "SO"))
		set_texture(&game->textures->SO, value, "SO");
	else if (is_equal(id, "WE"))
		set_texture(&game->textures->WE, value, "WE");
	else if (is_equal(id, "EA"))
		set_texture(&game->textures->EA, value, "EA");
	else if (is_equal(id, "F"))
		set_rgb(&game->textures->F, value, "F");
	else if (is_equal(id, "C"))
		set_rgb(&game->textures->C, value, "C");
	else
	{
		free(id);
		free(trimmed);
		return (-1);
	}
	free(id);
	free(trimmed);
	return (1);
}

static int	is_config_all_set(t_game *game)
{
	if (game->textures->NO && game->textures->SO
		&& game->textures->WE && game->textures->EA
		&& game->textures->F != -1 && game->textures->C != -1)
		return (1);
	return (0);
}
// TODO: organize all error messages (ENUM? MACROS?)
// TODO: decide how to print errors (custom perror?)
void	read_cub(char *path, t_game *game)
{
	int		fd;
	char	*line;
	int		parse_result;

	fd = open(path, O_RDONLY);
	ft_printf("path: %s\n", path);
	if (fd < 0)
	{
		perror("Error opening file");
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		parse_result = parse_config_line(line, game);
		if (parse_result == -1)
			break;
		free(line);
		line = get_next_line(fd);
	}
	if (!is_config_all_set(game))
	{
		ft_printf("Error: Invalid identifier or incomplete configuration.\n");
		if (line)
			free(line);
		close(fd);
		exit(1);
	}
	if (!line)
	{
		ft_printf("Error: Map not found in file.\n");
		close(fd);
		exit(1);
	}
	// parse_map(fd, line, game);
	free(line);
	close(fd);
}
