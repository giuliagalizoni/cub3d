NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I./include -I./library/minilibx_opengl_20191021

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
PARSER_DIR	= $(SRC_DIR)/parsing
RENDER_DIR	= $(SRC_DIR)/render
INPUT_DIR	= $(SRC_DIR)/input
UTILS_DIR	= $(SRC_DIR)/utils

# Source files
SRCS		= $(SRC_DIR)/main.c \
		  $(RENDER_DIR)/window.c \
		  $(RENDER_DIR)/render.c \
		  $(RENDER_DIR)/raycasting.c \
		  $(RENDER_DIR)/wall_drawing.c \
		  $(INPUT_DIR)/input.c \
		  $(INPUT_DIR)/movement.c \
		  $(PARSER_DIR)/parser.c

# Object files
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# MinilibX
MLX_DIR		= library/minilibx_opengl_20191021
MLX_LIB		= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -framework OpenGL -framework AppKit

# Libft
LIBFT_DIR	= libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a
LIBFT_INC	= -I$(LIBFT_DIR)


# Rules
all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(OBJS) -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -lm -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBFT_INC) -c $< -o $@

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
