#ifndef CUB3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_map {
		char **arr;
		int    width;
		int    height;
		//...
} t_map;

typedef struct player {
		int x; // position
		int y; // on the map
		char direction; // N S W E
} t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
}	t_img;

typedef struct s_textures {
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	t_img *NOimg;
	t_img *SOimg;
	t_img *WEimg;
	t_img *EAimg;
	int    F; // bitwise or make a separate struct for rgb
	int    C;
} t_textures;

typedef struct s_game {
		void *mlx;
		void *win;
		t_player *player;
		t_map *map;
		t_textures *textures;
		// ...
} t_game;

void	parser(char *path, t_game *game);

#endif
