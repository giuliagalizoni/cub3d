#include "../../include/cub3d.h"

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

double	calculate_ray_angle(t_game *game, int x)
{
	double	camera_x;
	double	ray_angle;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray_angle = game->player->angle + atan(camera_x * tan(FOV * DR / 2));
	return (ray_angle);
}

double	cast_single_ray(t_game *game, double ray_angle)
{
	double	ray_x;
	double	ray_y;
	double	dx;
	double	dy;
	double	distance;

	ray_x = game->player->x;
	ray_y = game->player->y;
	dx = cos(ray_angle) * 0.01;
	dy = sin(ray_angle) * 0.01;
	distance = 0;
	while (!is_wall(game, (int)ray_x, (int)ray_y))
	{
		ray_x += dx;
		ray_y += dy;
		distance += 0.01;
	}
	return (distance * cos(ray_angle - game->player->angle));
}

double	calculate_wall_height(double distance)
{
	double	wall_height;

	if (distance <= 0)
		return (WIN_HEIGHT);
	wall_height = WIN_HEIGHT / distance;
	if (wall_height > WIN_HEIGHT)
		wall_height = WIN_HEIGHT;
	return (wall_height);
}

double	perform_dda_loop(t_game *game, t_dda_vars *vars, int *wall_side)
{
	while (vars->hit == 0)
	{
		if (vars->side_dist_x < vars->side_dist_y)
		{
			vars->side_dist_x += vars->delta_dist_x;
			vars->map_x += vars->step_x;
			*wall_side = 0;
		}
		else
		{
			vars->side_dist_y += vars->delta_dist_y;
			vars->map_y += vars->step_y;
			*wall_side = 1;
		}
		if (is_wall(game, vars->map_x, vars->map_y))
			vars->hit = 1;
	}
	if (*wall_side == 0)
		return (vars->side_dist_x - vars->delta_dist_x);
	else
		return (vars->side_dist_y - vars->delta_dist_y);
}

void	init_player(t_game *game, double x, double y, char direction)
{
	game->player->x = x + 0.5;
	game->player->y = y + 0.5;
	if (direction == 'N')
	{
		game->player->angle = 3 * PI / 2;
		game->player->dx = 0;
		game->player->dy = -1;
		game->player->plane_x = 0.66;
		game->player->plane_y = 0;
	}
	else if (direction == 'S')
	{
		game->player->angle = PI / 2;
		game->player->dx = 0;
		game->player->dy = 1;
		game->player->plane_x = -0.66;
		game->player->plane_y = 0;
	}
	else if (direction == 'E')
	{
		game->player->angle = 0;
		game->player->dx = 1;
		game->player->dy = 0;
		game->player->plane_x = 0;
		game->player->plane_y = 0.66;
	}
	else if (direction == 'W')
	{
		game->player->angle = PI;
		game->player->dx = -1;
		game->player->dy = 0;
		game->player->plane_x = 0;
		game->player->plane_y = -0.66;
	}
}

void	cleanup_game(t_game *game)
{
	if (game->textures && game->textures->loaded)
		free_textures(game);
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
}

int	is_valid_position(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->map->width)
		return (0);
	if (map_y < 0 || map_y >= game->map->height)
		return (0);
	if (game->map->arr[map_y][map_x] == '1')
		return (0);
	return (1);
}

int	check_collision(t_game *game, double x, double y)
{
	double	radius;
	int		check_x;
	int		check_y;

	radius = 0.2;
	check_x = (int)(x - radius);
	check_y = (int)(y - radius);
	if (!is_valid_position(game, check_x, check_y))
		return (1);
	check_x = (int)(x + radius);
	check_y = (int)(y - radius);
	if (!is_valid_position(game, check_x, check_y))
		return (1);
	check_x = (int)(x - radius);
	check_y = (int)(y + radius);
	if (!is_valid_position(game, check_x, check_y))
		return (1);
	check_x = (int)(x + radius);
	check_y = (int)(y + radius);
	if (!is_valid_position(game, check_x, check_y))
		return (1);
	return (0);
}

int	calculate_texture_y(t_img *texture, int y, int wall_start, int wall_height)
{
	int	tex_y;
	int	relative_y;

	relative_y = y - wall_start;
	if (wall_height <= 0)
		return (0);
	tex_y = (relative_y * texture->height) / wall_height;
	if (tex_y < 0)
		tex_y = 0;
	else if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	return (tex_y);
}

int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*dst;
	int		color;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

t_img	*get_wall_texture_by_type(t_game *game, char wall_type,
		int wall_side, double ray_angle)
{
	t_img	*base_texture;

	base_texture = get_wall_texture_advanced(game, wall_side, ray_angle);
	if (wall_type == '1')
		return (base_texture);
	else if (wall_type == '2')
		return (&game->textures->imgs[0]);
	else if (wall_type == '3')
		return (&game->textures->imgs[1]);
	else if (wall_type == '4')
		return (&game->textures->imgs[2]);
	else
		return (base_texture);
}

int	calculate_texture_x_with_flip(t_img *texture, double wall_x,
		int wall_side, double ray_dir_x, double ray_dir_y)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)texture->width);
	if ((wall_side == 0 && ray_dir_x < 0) || (wall_side == 1 && ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

void	debug_prints(t_game game)
{
	int	i;

	ft_printf("NO: %s\n", game.textures->no);
	ft_printf("SO: %s\n", game.textures->so);
	ft_printf("WE: %s\n", game.textures->we);
	ft_printf("EA: %s\n", game.textures->ea);
	ft_printf("F: %d\n", game.textures->f);
	ft_printf("C: %d\n", game.textures->c);
	ft_printf("\n## MAP ARR##\n");
	i = 0;
	while (game.map->arr[i])
	{
		ft_printf("%s\n", game.map->arr[i]);
		i++;
	}
	ft_printf("\n");
	ft_printf("map height: %d\n", game.map->height);
	ft_printf("map width: %d\n", game.map->width);
	ft_printf("player position x: %d\n", game.map->player_x);
	ft_printf("player position y: %d\n", game.map->player_y);
	ft_printf("player direction: %c\n", game.map->player_dir);
}

int	setup_game(t_game *game)
{
	game->floor_color = mlx_get_color_value(game->mlx, game->textures->f);
	game->ceiling_color = mlx_get_color_value(game->mlx, game->textures->c);
	if (!load_all_textures(game))
	{
		ft_printf("Error: Failed to load textures\n");
		cleanup_parsing(game);
		return (0);
	}
	if (!init_screen_image(game))
	{
		cleanup_parsing(game);
		return (0);
	}
	return (1);
}
