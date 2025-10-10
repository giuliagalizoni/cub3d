#include "../../include/cub3d.h"

#define TILESIZE 10
#define MM_BG 0x101010
#define MM_WALL 0x228B22
#define MM_FLOOR 0x3d423e
#define MM_PLAYER 0xFF0000

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || x < 0 || y < 0 || x >= img->width || y >= img->height)
		return;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

static void	fill_circle(t_img *img, int cx, int cy, int radius)
{
	int	x;
	int	y;
	int	radius_sq;

	radius_sq = radius * radius;
	y = cy - radius;
	while (y <= cy + radius)
	{
		x = cx - radius;
		while (x <= cx + radius)
		{
			if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius_sq)
			{
				if (x >= 0 && x < img->width && y >= 0 && y < img->height)
					my_mlx_pixel_put(img, x, y, MM_PLAYER);
			}
			x++;
		}
		y++;
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
				fill_tile(&game->minimap, x * TILESIZE, y * TILESIZE, MM_WALL);
			else if (cell == '0')
				fill_tile(&game->minimap, x * TILESIZE, y * TILESIZE, MM_FLOOR);
			else
				fill_tile(&game->minimap, x * TILESIZE, y * TILESIZE, MM_BG);
			x++;
		}
		y++;
	}
	fill_circle(&game->minimap, (int)(game->player->x * TILESIZE),
		(int)(game->player->y * TILESIZE), TILESIZE / 3);
}
