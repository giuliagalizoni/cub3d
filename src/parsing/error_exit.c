#include "../../include/cub3d.h"

static char	*get_err_message(t_error err_code)
{
	static char	*messages[15];

	messages[ERR_USAGE] = "Usage: ./cub3d <map.cub>";
	messages[ERR_MALLOC] = "Memory allocation failed";
	messages[ERR_FILE_EXT] = "Invalid file extension";
	messages[ERR_FILE_OPEN] = "Failed to open file";
	messages[ERR_DUPLICATE_ID] = "Duplicate identifier found";
	messages[ERR_INVALID_ID] = "Invalid identifier in map file";
	messages[ERR_INVALID_RGB] = "Invalid RGB color format or value";
	messages[ERR_MISSING_CONFIG] = "One or more texture/color configurations are invalid or missing";
	messages[ERR_MISSING_MAP] = "Map is missing";
	messages[ERR_EMPTY_LINE_MAP] = "Map contains an empty line";
	messages[ERR_INVALID_CHAR_MAP] = "Map contains an invalid character";
	messages[ERR_DUPLICATE_PLAYER] = "Map contains more than one player start position";
	messages[ERR_MISSING_PLAYER] = "Map does not contain a player start position";
	messages[ERR_MAP_NOT_CLOSED] = "Map is not enclosed by walls";
	messages[ERR_SYSTEM] = NULL;
	if (err_code >= 0 && err_code < 15)
		return (messages[err_code]);
	return ("An unknown error occurred");
}

void	ft_perror(t_error err_code, char *context)
{
	ft_putstr_fd("Error: ", 2);
	if (err_code == ERR_SYSTEM && context)
		perror(context);
	else
	{
		if (context)
		{
			ft_putstr_fd(context, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putstr_fd(get_err_message(err_code), 2);
		ft_putstr_fd("\n", 2);
	}
}

void	error_exit(t_error err_code, t_game *game, char *context)
{
	ft_perror(err_code, context);
	cleanup_parsing(game);
	cleanup_game(game); // do we need this?
	exit(EXIT_FAILURE);
}
