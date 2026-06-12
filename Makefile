# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/17 15:15:33 by lsarraci          #+#    #+#              #
#    Updated: 2026/05/05 17:15:08 by lsarraci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS_DIR = src
OBJS_DIR = objs
LIB_DIR = lib
LIBFT_DIR = $(LIB_DIR)/libft
MLX_DIR = $(LIB_DIR)/minilibx-linux

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -I$(LIBFT_DIR) -I$(LIB_DIR)/$(MLX_DIR) -Iinclude
MLX_LINK = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

SRC = main.c \
	  init.c \
	  hooks.c \
	  window.c \
	  frees.c \

ENGINE_DIR = engine
SRC += $(ENGINE_DIR)/movement.c \
		$(ENGINE_DIR)/camera.c \
		$(ENGINE_DIR)/first_ray.c \
		$(ENGINE_DIR)/vision_ray.c \
		$(ENGINE_DIR)/collision.c \
		$(ENGINE_DIR)/dda.c \
		$(ENGINE_DIR)/raycaster_init.c \
		$(ENGINE_DIR)/raycaster_color.c \
		$(ENGINE_DIR)/raycaster_column.c \
		$(ENGINE_DIR)/raycaster_utils.c \

INPUT_DIR = input
SRC += $(INPUT_DIR)/arrows.c \

PARSER_DIR = parser
SRC += $(PARSER_DIR)/parse_map.c \
	   $(PARSER_DIR)/parse_element.c \
	   $(PARSER_DIR)/error_handler.c \
	   $(PARSER_DIR)/validate_grid.c \
	   $(PARSER_DIR)/validator.c \
	   $(PARSER_DIR)/init_map.c \
	   $(PARSER_DIR)/map_utils.c \

RENDER_DIR = render
SRC += $(RENDER_DIR)/render.c \
	   $(RENDER_DIR)/minimap_layer.c \
	   $(RENDER_DIR)/minimap_layer_utils.c \
	   $(RENDER_DIR)/raycaster_layer.c \
	   $(RENDER_DIR)/bg_layer.c \
	   $(RENDER_DIR)/pixel.c \
	   $(RENDER_DIR)/shapes.c \
	   $(RENDER_DIR)/render_utils.c \
	   $(RENDER_DIR)/nine_point.c \
	   $(RENDER_DIR)/texture.c \

UTILS_DIR = utils
SRC += $(UTILS_DIR)/time_utils.c \
	   $(UTILS_DIR)/minimap_player.c \
	   $(UTILS_DIR)/minimap_utils.c \
	   $(UTILS_DIR)/minimap.c \



SRC := $(addprefix $(SRCS_DIR)/, $(SRC))

OBJS = $(SRC:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(LIBFT):
	@ echo "Building Libft library..."
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	@echo "Libft library built successfully."

$(MLX):
	@ echo "Building MinilibX library..."
	@$(MAKE) -C $(MLX_DIR) > /dev/null
	@echo "MinilibX library built successfully."

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "Linking object files and libraries to create executable..."
	@$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^ $(MLX_LINK) > /dev/null
	@echo "Executable $(NAME) created successfully."

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ > /dev/null
	@echo "Compiling $< -> $@"

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Cleaning MinilibX object files..."
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null
	@echo "Cleaning object files..."
	rm -rf $(OBJS_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null
	@echo "Cleaning executable..."
	rm -rf $(NAME)
	@echo "Cleaned library and executable."

re: fclean all

valgrind:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=mlx.supp ./$(NAME)

.PHONY: all clean fclean re


