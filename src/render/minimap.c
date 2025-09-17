#include "../../include/cub3d.h"

# define TILESIZE 10
#define MM_BG 0x000000
#define MM_WALL 0x228B22
#define MM_FLOOR 0x101010
#define MM_PLAYER 0x00FF00


void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	fill_tile(t_img *img, int sx, int sy, int color)
{
    int	i;
    int	j;

    i = 0;
    while (i < TILESIZE)
    {
        j = 0;
        while (j < TILESIZE)
        {
            my_mlx_pixel_put(img, sx + j, sy + i, color);
            j++;
        }
        i++;
    }
}
void	init_minimap(t_game *game)
{
    game->minimap.width = game->map->width * TILESIZE;
    game->minimap.height = game->map->height * TILESIZE;
    game->minimap.img = mlx_new_image(game->mlx,
            game->minimap.width, game->minimap.height);
    if (!game->minimap.img)
        error_exit(ERR_IMG_CREATE, game, NULL);
    game->minimap.addr = mlx_get_data_addr(game->minimap.img,
            &game->minimap.bits_per_pixel,
            &game->minimap.line_length,
            &game->minimap.endian);
    if (!game->minimap.addr)
        error_exit(ERR_IMG_DATA_ADDR, game, NULL);
}

void	draw_line(t_img *img, int x1, int y1, int x2, int y2, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = x2 - x1;
	if (dx < 0)
		dx = -dx;
	dy = y2 - y1;
	if (dy < 0)
		dy = -dy;

	if (x1 < x2)
		sx = 1;
	else
		sx = -1;
	if (y1 < y2)
		sy = 1;
	else
		sy = -1;

	err = dx - dy;
	while (1)
	{
		my_mlx_pixel_put(img, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err = err - dy;
			x1 = x1 + sx;
		}
		if (e2 < dx)
		{
			err = err + dx;
			y1 = y1 + sy;
		}
	}
}

void	draw_minimap_rays(t_game *game, int screen_w)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	ray_x;
	double	ray_y;
	int		i;

	x = 0;
	while (x < screen_w)
	{
		camera_x = 2 * x / (double)screen_w - 1;
		ray_dir_x = game->player->dx + game->player->plane_x * camera_x;
		ray_dir_y = game->player->dy + game->player->plane_y * camera_x;

		ray_x = game->player->x;
		ray_y = game->player->y;
		i = 0;
		while (i < 30) // limit ray length in tiles
		{
			if (ray_x < 0 || ray_y < 0
				|| ray_x >= game->map->width
				|| ray_y >= game->map->height)
				break ;
			if (game->map->arr[(int)ray_y][(int)ray_x] == '1')
				break ;
			ray_x += ray_dir_x * 0.1;
			ray_y += ray_dir_y * 0.1;
			i++;
		}

		draw_line(&game->minimap,
			(int)(game->player->x * TILESIZE),
			(int)(game->player->y * TILESIZE),
			(int)((game->player->x + game->player->dx * 5) * TILESIZE),
			(int)((game->player->y + game->player->dy * 5) * TILESIZE),
			0xFF0000);

		x += 10; // skip some rays so minimap doesn’t get too dense
	}
}

void	draw_minimap(t_game *game)
{
    int		y;
    int		x;
    char	cell;

    y = 0;
    while (y < game->map->height)
    {
        x = 0;
        while (x < game->map->width)
        {
            cell = game->map->arr[y][x];
            if (cell == '1')
                fill_tile(&game->minimap, x * TILESIZE, y * TILESIZE, game->ceiling_color);
            else
                fill_tile(&game->minimap, x * TILESIZE, y * TILESIZE, 0x000000);
            x++;
        }
        y++;
    }
    fill_tile(&game->minimap,
        (int)((game->player->x) * TILESIZE),
        (int)((game->player->y) * TILESIZE),
        0x00FF00);

}
