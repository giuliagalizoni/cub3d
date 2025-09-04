NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

# Detect OS
UNAME_S := $(shell uname -s)

# OS-specific settings
ifeq ($(UNAME_S),Darwin)
    # macOS
    MLX_DIR		= library/minilibx_opengl_20191021
    MLX_LIB		= $(MLX_DIR)/libmlx.a
    MLX_FLAGS	= -framework OpenGL -framework AppKit
    INCLUDES	= -I./include -I./$(MLX_DIR)
else
    # Linux
    MLX_DIR		= library/minilibx-linux
    MLX_LIB		= $(MLX_DIR)/libmlx.a
    MLX_FLAGS	= -lXext -lX11 -lm
    INCLUDES	= -I./include -I./$(MLX_DIR)
endif

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
PARSER_DIR	= $(SRC_DIR)/parsing
RENDER_DIR	= $(SRC_DIR)/render
INPUT_DIR	= $(SRC_DIR)/input
UTILS_DIR	= $(SRC_DIR)/utils
TEXTURE_DIR	= $(SRC_DIR)/textures

# Source files
SRCS		= $(SRC_DIR)/main.c \
		  $(RENDER_DIR)/window.c \
		  $(RENDER_DIR)/render.c \
		  $(RENDER_DIR)/raycasting.c \
		  $(RENDER_DIR)/wall_drawing.c \
		  $(INPUT_DIR)/input.c \
		  $(INPUT_DIR)/movement.c \
		  $(TEXTURE_DIR)/texture_loader.c \
		  $(TEXTURE_DIR)/texture_manager.c \
		  $(TEXTURE_DIR)/texture_utils.c \
		  $(PARSER_DIR)/parser.c \
		  $(PARSER_DIR)/read_cub.c \
		  $(PARSER_DIR)/parse_map.c \
		  $(PARSER_DIR)/parse_config.c \
		  $(PARSER_DIR)/validate_map.c \
		  $(PARSER_DIR)/scan_map.c \
		  $(PARSER_DIR)/cleanup.c \
		  $(UTILS_DIR)/array_utils.c \
		  $(UTILS_DIR)/string_utils.c \

# Object files
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# Libft
LIBFT_DIR	= libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a
LIBFT_INC	= -I$(LIBFT_DIR)

# Rules
all: setup_mlx $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(OBJS) -L$(MLX_DIR) -lmlx $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -lm -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I./include -I$(MLX_DIR) $(LIBFT_INC) -c $< -o $@

setup_mlx:
ifeq ($(UNAME_S),Darwin)
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Setting up macOS minilibx..."; \
		cd library && tar -xzf minilibx_macos_opengl.tgz; \
	fi
	@make -C $(MLX_DIR) 2>/dev/null || echo "minilibx already compiled"
else
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Setting up Linux minilibx..."; \
		cd library && tar -xzf minilibx-linux.tgz; \
	fi
	@make -C $(MLX_DIR) 2>/dev/null || echo "minilibx already compiled"
endif

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
ifeq ($(UNAME_S),Darwin)
	@make -C $(MLX_DIR) clean 2>/dev/null || true
else
	@make -C $(MLX_DIR) clean 2>/dev/null || true
endif
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re setup_mlx
