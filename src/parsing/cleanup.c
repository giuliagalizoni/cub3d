#include "../../include/cub3d.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	exhaust_gnl(int fd)
{
	char	*temp;

	if (fd < 0)
		return;
	temp = get_next_line(fd);
	while (temp)
	{
		free(temp);
		temp = get_next_line(fd);
	}
	close(fd);
}

void	cleanup_parsing(t_game *game)
{
	if (!game)
		return;
	if (game->map)
	{
		if (game->map->arr)
			free_arr(game->map->arr);
		free(game->map);
	}
	if (game->textures)
	{
		if (game->textures->NO)
			free(game->textures->NO);
		if (game->textures->SO)
			free(game->textures->SO);
		if (game->textures->WE)
			free(game->textures->WE);
		if (game->textures->EA)
			free(game->textures->EA);
		free(game->textures);
	}
	if (game->player)
		free(game->player);
}

static char	*get_err_message(t_error err_code)
{
	static char	*messages[14];

	messages[ERR_USAGE] = "Usage: ./cub3d <map.cub>";
	messages[ERR_MALLOC] = "Memory allocation failed";
	messages[ERR_FILE_EXT] = "Invalid file extension";
	messages[ERR_FILE_OPEN] = "Failed to open file";
	messages[ERR_DUPLICATE_ID] = "Duplicate texture or color identifier found";
	messages[ERR_INVALID_ID] = "Invalid identifier in map file";
	messages[ERR_INVALID_RGB] = "Invalid RGB color format or value";
	messages[ERR_MISSING_CONFIG] = "One or more texture/color configurations are missing";
	messages[ERR_MISSING_MAP] = "Map is missing";
	messages[ERR_EMPTY_LINE_MAP] = "Map contains an empty line";
	messages[ERR_INVALID_CHAR_MAP] = "Map contains an invalid character";
	messages[ERR_DUPLICATE_PLAYER] = "Map contains more than one player start position";
	messages[ERR_MISSING_PLAYER] = "Map does not contain a player start position";
	messages[ERR_MAP_NOT_CLOSED] = "Map is not enclosed by walls";
	if (err_code >= 0 && err_code < 14)
		return (messages[err_code]);
	return ("An unknown error occurred");
}

// char	*get_err_message(t_error err_code)
// {
// 	if (err_code == ERR_USAGE)
// 		return ("Usage: ./cub3d <map.cub>");
// 	if (err_code == ERR_MALLOC)
// 		return ("Memory allocation failed");
// 	if (err_code == ERR_FILE_EXT)
// 		return ("Invalid file extension");
// 	if (err_code == ERR_FILE_OPEN)
// 		return ("Failed to open file");
// 	if (err_code == ERR_DUPLICATE_ID)
// 		return ("Duplicate texture or color identifier found");
// 	if (err_code == ERR_INVALID_ID)
// 		return ("Invalid identifier in map file");
// 	if (err_code == ERR_INVALID_RGB)
// 		return ("Invalid RGB color format or value");
// 	if (err_code == ERR_MISSING_CONFIG)
// 		return ("One or more texture/color configurations are missing");
// 	if (err_code == ERR_EMPTY_LINE_MAP)
// 		return ("Map contains an empty line");
// 	if (err_code == ERR_INVALID_CHAR_MAP)
// 		return ("Map contains an invalid character");
// 	if (err_code == ERR_DUPLICATE_PLAYER)
// 		return ("Map contains more than one player start position");
// 	if (err_code == ERR_MISSING_PLAYER)
// 		return ("Map does not contain a player start position");
// 	if (err_code == ERR_MAP_NOT_CLOSED)
// 		return ("Map is not enclosed by walls");
// 	return ("An unknown error occurred");
// }

void	ft_perror(t_error err_code)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(get_err_message(err_code), 2);
	ft_putstr_fd("\n", 2);
}

void	error_exit(t_error err_code, t_game *game)
{
	ft_perror(err_code);
	cleanup_parsing(game);
	cleanup_game(game); // do we need this?
	exit(EXIT_FAILURE);
}
