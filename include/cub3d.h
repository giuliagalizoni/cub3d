#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

# ifdef __linux__
#  include "../library/minilibx-linux/mlx.h"
# else
#  include "../library/minilibx_opengl_20191021/mlx.h"
# endif

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define FOV 60

# ifdef __linux__
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_ESC 65307
# else
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_ESC 53
# endif

# define RED_CROSS 17
# define PI 3.14159265359
# define DR 0.0174533
# define MOVE_SPEED 0.08
# define ROTATION_SPEED 0.05

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

/* Error Codes Enum */
typedef enum e_error
{
    ERR_USAGE,
    ERR_MALLOC,
    ERR_FILE_EXT,
    ERR_FILE_OPEN,
    ERR_DUPLICATE_ID,
    ERR_INVALID_ID,
    ERR_INVALID_RGB,
    ERR_MISSING_CONFIG,
	  ERR_MISSING_MAP,
    ERR_EMPTY_LINE_MAP,
    ERR_INVALID_CHAR_MAP,
    ERR_DUPLICATE_PLAYER,
    ERR_MISSING_PLAYER,
    ERR_MAP_NOT_CLOSED,
	  ERR_SYSTEM
}	t_error;

/* Player structure */
typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	dx;
	double	dy;
	double	plane_x;
	double	plane_y;
	char	direction;
}	t_player;

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

typedef struct s_flip_params
{
	t_img	*texture;
	double	wall_x;
	int		wall_side;
	double	ray_dir_x;
	double	ray_dir_y;
}	t_flip_params;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
	t_img	imgs[4];
	int		loaded;
}	t_textures;

typedef struct s_map
{
	char	**arr;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_dda_vars
{
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
}	t_dda_vars;

typedef struct s_ray_data
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		wall_side;
	double	wall_x;
}	t_ray_data;

typedef struct s_texture_draw
{
	int		start_y;
	int		end_y;
	t_img	*texture;
	int		tex_x;
	double	tex_step;
	double	tex_pos;
	t_flip_params	flip_params;
}	t_texture_draw;

typedef struct s_wall_calc
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
}	t_wall_calc;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_player	*player;
	t_keys		keys;
	t_map		*map;
	t_textures	*textures;
	int			floor_color;
	int			ceiling_color;
}	t_game;

void	parser(char *path, t_game *game);
void	read_cub(char *path, t_game *game);
int		parse_config_line(char *line, t_game *game);
void	parse_map(int fd, char *first_line, t_game *game);
void	scan_map(t_map *map, t_game *game);
void	validade_map(t_game *game);

/* Function prototypes - Window management */

int		init_window(t_game *game);
int		close_window(t_game *game);
void	cleanup_game(t_game *game);
void	debug_prints(t_game game);
int		setup_game(t_game *game);
int		init_rendering(t_game *game);
int		render_frame(t_game *game);
void	clear_image(t_img *img, int color);
void	put_pixel(t_img *img, int x, int y, int color);
int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
void	update_movement(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
int		is_valid_position(t_game *game, double x, double y);
int		check_collision(t_game *game, double x, double y);
int		init_screen_image(t_game *game);
void	setup_hooks(t_game *game);
void	draw_floor_ceiling(t_game *game);
void	cast_rays(t_game *game);
double	calculate_ray_angle(t_game *game, int x);
double	cast_single_ray(t_game *game, double ray_angle);
double	cast_ray_dda_standard(t_game *game, t_ray_data *ray_data);
double	calculate_wall_height(double distance);
double	perform_dda_loop(t_game *game, t_dda_vars *vars, int *wall_side);
void	draw_wall_slice(t_game *game, int x, double wall_height);
void	draw_wall_slice_textured(t_game *game, int x, double wall_height,
		t_ray_data *ray_data);
int		is_wall(t_game *game, int x, int y);
void	init_player(t_game *game, double x, double y, char direction);
void	set_player_direction(t_player *player, char direction);
void	set_default_colors(t_game *game);

int		load_texture(t_game *game, t_img *texture, char *path);
int		load_all_textures(t_game *game);
int		load_textures(t_game *game);
void	free_textures(t_game *game);
t_img	*get_wall_texture(t_game *game, int wall_side);
t_img	*get_wall_texture_advanced(t_game *game, int wall_side, double ray_angle);
t_img	*get_wall_texture_by_direction(t_game *game, int wall_side,
			double ray_dir_x, double ray_dir_y);
int		calculate_texture_x(t_img *texture, double wall_x);
int		calculate_texture_x_with_flip(t_flip_params *params);
int		calculate_texture_y(t_img *texture, int y, int wall_start,
			int wall_height);
int		get_texture_pixel(t_img *texture, int x, int y);
double	calculate_wall_x(t_game *game, double ray_angle, int wall_side);

/* Function prototypes - Cleaning */
void	free_arr(char **arr);
void	cleanup_parsing(t_game *game);
void	exhaust_gnl(int fd);
void	ft_perror(t_error err_code, char *context);
void	error_exit(t_error err_code, t_game *game, char *context);

/* Utils */
int		arr_size(char **arr);
int		is_equal(char *str1, char *str2);
char	*get_first_word(char *line);

#endif
