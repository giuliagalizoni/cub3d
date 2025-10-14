/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalizon <ggalizon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:49:47 by ggalizon          #+#    #+#             */
/*   Updated: 2025/10/14 16:55:50 by ggalizon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
		result = set_rgb(&game->textures->f, value);
	else if (is_equal(id, "C"))
		result = set_rgb(&game->textures->c, value);
	else
		return (0);
	return (result);
}

static void	quit_config(t_game *game, t_error err_code, char *line, int fd)
{
	free(line);
	exhaust_gnl(fd);
	error_exit(err_code, game, NULL);
}

static int	handle_config_error(int result, t_game *game, char *line, int fd)
{
	if (result == -1)
		quit_config(game, ERR_INVALID_RGB, line, fd);
	if (result == -2)
		quit_config(game, ERR_DUPLICATE_ID, line, fd);
	if (result == -3)
		quit_config(game, ERR_MALLOC, line, fd);
	if (result == -4)
		quit_config(game, ERR_FILE_EXT, line, fd);
	if (result == 0)
		return (-1);
	return (1);
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
	return (handle_config_error(result, game, line, fd));
}
