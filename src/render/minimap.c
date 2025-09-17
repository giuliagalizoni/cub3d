#include "../../include/cub3d.h"

# define TILESIZE 5

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
                fill_tile(&game->minimap, x * TILESIZE, y * TILESIZE, 0x444444);
            else
                fill_tile(&game->minimap, x * TILESIZE, y * TILESIZE, 0x000000);
            x++;
        }
        y++;
    }
    fill_tile(&game->minimap,
        (int)(game->map->player_x * TILESIZE),
        (int)(game->map->player_y * TILESIZE), 0x00FF00);
    mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 10, 10);
}
