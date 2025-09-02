#include "../../include/cub3d.h"

int	is_equal(char *str1, char *str2)
{
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	if (!ft_strncmp(str1, str2, ft_strlen(str2)))
		return (1);
	return (0);
}

static void	set_texture(t_game *game, char **field, char *path, char *id)
{
	if (*field)
		error_exit(ERR_DUPLICATE_ID, game, id);
	*field = ft_strdup(path);
}

static int	arr_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

static int	parse_rgb(char *rgb_str, t_game *game)
{
	int	r;
	int	g;
	int	b;
	char **rgb_arr;

	rgb_arr = ft_split(rgb_str, ',');
	if (!rgb_arr || arr_size(rgb_arr) != 3)
	{
		if (rgb_arr)
			free_arr(rgb_arr);
		error_exit(ERR_INVALID_RGB, game, rgb_str);
	}
	r = ft_atoi(rgb_arr[0]);
	g = ft_atoi(rgb_arr[1]);
	b = ft_atoi(rgb_arr[2]);
	free_arr(rgb_arr);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit(ERR_INVALID_RGB, game, rgb_str);
	return ((r << 16) | (g << 8) | b);
}

static void	set_rgb(t_game *game, int *field, char *rgb_str, char *id)
{
	if (*field != -1)
		error_exit(ERR_DUPLICATE_ID, game, id);
	*field = parse_rgb(rgb_str, game);
}

char	*get_first_word(char *line)
{
	int	i;
	int	start;
	int	end;

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
		return (free(trimmed), 0);
	id = get_first_word(trimmed);
	value = trimmed + ft_strlen(id);
	while (*value == ' ' || *value == '\t')
		value++;
	if (is_equal(id, "NO"))
		set_texture(game, &game->textures->NO, value, id);
	else if (is_equal(id, "SO"))
		set_texture(game, &game->textures->SO, value, id);
	else if (is_equal(id, "WE"))
		set_texture(game, &game->textures->WE, value, id);
	else if (is_equal(id, "EA"))
		set_texture(game, &game->textures->EA, value, id);
	else if (is_equal(id, "F"))
		set_rgb(game, &game->textures->F, value, id);
	else if (is_equal(id, "C"))
		set_rgb(game, &game->textures->C, value, id);
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
void	read_cub(char *path, t_game *game)
{
	int		fd;
	char	*line;
	int		parse_result;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit(ERR_FILE_OPEN, game, path);
	line = get_next_line(fd);
	while (line)
	{
		parse_result = parse_config_line(line, game);
		if (parse_result == -1)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (!is_config_all_set(game))
	{
		if (line)
			free(line);
		exhaust_gnl(fd);
		error_exit(ERR_MISSING_CONFIG, game, NULL); // maybe change the message
	}
	if (!line)
	{
		close(fd);
		error_exit(ERR_MISSING_MAP, game, NULL);
	}
	parse_map(fd, line, game);
	free(line);
	close(fd);
}
