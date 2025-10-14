/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalizon <ggalizon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:49:47 by ggalizon          #+#    #+#             */
/*   Updated: 2025/10/13 18:24:55 by ggalizon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

static int	set_rgb(t_game *game, int *field, char *rgb_str)
{
	int	color;

	if (*field != -1)
		return (-2);
	color = parse_rgb(rgb_str, game);
	if (color == -1)
		return (-1);
	*field = color;
	return (1);
}

static int	check_texture_ext(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len <= 4)
		return (0);
	if (path[len - 4] != '.')
		return (0);
	if (path[len - 3] != 'x')
		return (0);
	if (path[len - 2] != 'p')
		return (0);
	if (path[len - 1] != 'm')
		return (0);
	return (1);
}

static int	set_texture(char **field, char *path)
{
	if (*field)
		return (-2);
	if (!check_texture_ext(path))
		return (-4);
	*field = ft_strdup(path);
	if (!*field)
		return (-3);
	return (1);
}

static int	set_config_value(t_game *game, char *id, char *value)
{
	int	result;

	if (is_equal(id, "NO"))
		result = set_texture(&game->textures->no, value);
	else if (is_equal(id, "SO"))
		result = set_texture(&game->textures->so, value);
	else if (is_equal(id, "WE"))
		result = set_texture(&game->textures->we, value);
	else if (is_equal(id, "EA"))
		result = set_texture(&game->textures->ea, value);
	else if (is_equal(id, "F"))
		result = set_rgb(game, &game->textures->f, value);
	else if (is_equal(id, "C"))
		result = set_rgb(game, &game->textures->c, value);
	else
		return (0);
	return (result);
}

int	parse_config_line(char *line, t_game *game, int fd)
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
	if (result == -1)
	{
		free(line);
		exhaust_gnl(fd);
		error_exit(ERR_INVALID_RGB, game, NULL);
	}
	if (result == -2)
	{
		free(line);
		exhaust_gnl(fd);
		error_exit(ERR_DUPLICATE_ID, game, NULL);
	}
	if (result == -3)
	{
		free(line);
		exhaust_gnl(fd);
		error_exit(ERR_MALLOC, game, NULL);
	}
	if (result == -4)
	{
		free(line);
		exhaust_gnl(fd);
		error_exit(ERR_FILE_EXT, game, NULL);
	}
	if (result == 0)
		return (-1);
	return (1);
}
