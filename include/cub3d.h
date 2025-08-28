#ifndef CUB3D_H
# define CUB3D_H


# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

/* Detect OS and include appropriate mlx.h */
#ifdef __linux__
# include "../library/minilibx-linux/mlx.h"
#else
# include "../library/minilibx_opengl_20191021/mlx.h"
#endif

/* Window settings */
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define FOV 60

/* Key codes - Linux vs macOS */
#ifdef __linux__
/* Linux key codes */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
#else
/* macOS key codes */
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53
#endif

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
	char	direction;
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

typedef struct s_textures {
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	int    F; // bitwise or make a separate struct for rgb
	int    C;
	t_img		imgs[4];
} t_textures;

typedef struct s_map {
		char **arr;
		int	width;
		int	height;
		int	player_x;
		int	player_y;
		char	player_dir;
} t_map;

/* Game data structure */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_player	*player; // this needs to be a pointer, no?
	t_map		*map;
	t_textures	*textures;
// move this to the struct?
	int			floor_color;
	int			ceiling_color;
}	t_game;

/*Function prototypes - Parsing*/
void	parser(char *path, t_game *game);
void	read_cub(char *path, t_game *game);
void	parse_map(int fd, char *first_line, t_game *game);
int	scan_map(t_map *map);
void	validade_map(t_map *map);

int	is_equal(char *str1, char *str2);

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
