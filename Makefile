test:
	make -C libft && gcc -g -Wall -Wextra -Werror src/*.c src/parsing/*.c -Llibft -lft -o cub3d

