#include "../../include/cub3d.h"

int	determine_wall_side(t_game *game, double ray_angle, int map_x, int map_y)
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		side;

	(void)game;
	(void)map_x;
	(void)map_y;
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	if (ray_dir_x > 0)
		side = 3; // East
	else
		side = 2; // West
	if (ray_dir_y > 0)
		side = 1; // South
	else
		side = 0; // North
	return (side);
}

double	calculate_wall_x(t_game *game, double ray_angle, int wall_side)
{
	double	wall_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;

	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	map_x = (int)game->player->x;
	map_y = (int)game->player->y;
	if (ray_dir_x < 0)
		step_x = -1;
	else
		step_x = 1;
	if (ray_dir_y < 0)
		step_y = -1;
	else
		step_y = 1;
	if (wall_side == 0)
	{
		perp_wall_dist = (map_x - game->player->x + (1 - step_x) / 2.0) / ray_dir_x;
		wall_x = game->player->y + perp_wall_dist * ray_dir_y;
	}
	else
	{
		perp_wall_dist = (map_y - game->player->y + (1 - step_y) / 2.0) / ray_dir_y;
		wall_x = game->player->x + perp_wall_dist * ray_dir_x;
	}
	wall_x -= floor(wall_x);
	return (wall_x);
}

int	validate_texture_file(char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}
