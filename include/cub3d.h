/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:38:23 by shutan            #+#    #+#             */
/*   Updated: 2025/08/21 18:38:25 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../library/minilibx_opengl_20191021/mlx.h"

/* Window settings */
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define FOV 60

/* Key codes for macOS */
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

/* Colors */
# define RED_CROSS 17

/* Math constants */
# define PI 3.14159265359
# define DR 0.0174533

/* Player structure */
typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	dx;
	double	dy;
}	t_player;

/* Image structure for textures */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* Game data structure */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_player	player;
	char		**map;
	int			map_width;
	int			map_height;
	t_img		textures[4];
	int			floor_color;
	int			ceiling_color;
}	t_game;

/* Function prototypes - Window management */
int		init_window(t_game *game);
int		close_window(t_game *game);
void	cleanup_game(t_game *game);

/* Function prototypes - Rendering */
int		render_frame(t_game *game);
void	clear_image(t_img *img, int color);
void	put_pixel(t_img *img, int x, int y, int color);

/* Function prototypes - Input handling */
int		handle_keypress(int keycode, t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
int		is_valid_position(t_game *game, double x, double y);

/* Function prototypes - Rendering */
int		init_screen_image(t_game *game);
void	setup_hooks(t_game *game);
void	draw_floor_ceiling(t_game *game);

/* Function prototypes - Raycasting */
void	cast_rays(t_game *game);
double	calculate_ray_angle(t_game *game, int x);
double	cast_single_ray(t_game *game, double ray_angle);
double	calculate_wall_height(double distance);
void	draw_wall_slice(t_game *game, int x, double wall_height);
int		is_wall(t_game *game, int x, int y);

/* Function prototypes - Game initialization */
void	init_player(t_game *game, double x, double y, char direction);
void	set_default_colors(t_game *game);

#endif
