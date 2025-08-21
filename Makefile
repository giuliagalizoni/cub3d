# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: your_login <your_login@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by your_login       #+#    #+#              #
#    Updated: 2024/01/01 00:00:00 by your_login      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I./include -I./library/minilibx_opengl_20191021

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
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
			  $(INPUT_DIR)/movement.c

# Object files
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# MinilibX
MLX_DIR		= library/minilibx_opengl_20191021
MLX_LIB		= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -framework OpenGL -framework AppKit

# Rules
all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L$(MLX_DIR) -lmlx $(MLX_FLAGS) -lm -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
