#include "../../include/cub3d.h"

static int	parse_rgb(char *rgb_str, t_game *game)
{
	int		r;
	int		g;
	int		b;
	char	**rgb_arr;

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

static void	set_texture(t_game *game, char **field, char *path, char *id)
{
	if (*field)
		error_exit(ERR_DUPLICATE_ID, game, id);
	*field = ft_strdup(path);
}

static int	set_config_value(t_game *game, char *id, char *value)
{
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
		return (-1);
	return (1);
}

int	parse_config_line(char *line, t_game *game)
{
	char	*trimmed;
	char	*id;
	char	*value;
	int		result;

	trimmed = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed)
		return (0);
	if (!*trimmed)
		return (free(trimmed), 0);
	id = get_first_word(trimmed);
	value = trimmed + ft_strlen(id);
	while (*value == ' ' || *value == '\t')
		value++;
	result = set_config_value(game, id, value);
	free(id);
	free(trimmed);
	return (result);
}
