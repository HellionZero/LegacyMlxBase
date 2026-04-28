# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsarraci <lsarraci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/17 15:15:33 by lsarraci          #+#    #+#              #
#    Updated: 2026/04/28 16:44:09 by lsarraci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS_DIR = src
OBJS_DIR = objs
LIB_DIR = lib
LIBFT_DIR = $(LIB_DIR)/libft
MLX_DIR = $(LIB_DIR)/minilibx-linux

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I$(LIBFT_DIR) -I$(LIB_DIR)/$(MLX_DIR) -Iinclude
MLX_LINK = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

SRC = main.c \
	  init.c \
	  hooks.c \
	  window.c \

DEBUG_DIR = debug
SRC += $(DEBUG_DIR)/map_debug.c \

RENDER_DIR = render
SRC += $(RENDER_DIR)/render.c \
	   $(RENDER_DIR)/minimap_layer.c \
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

INPUT_DIR = input
SRC += $(INPUT_DIR)/arrows.c \

SRC := $(addprefix $(SRCS_DIR)/, $(SRC))

OBJS = $(SRC:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^ $(MLX_LINK)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(NAME)

re: fclean all

valgrind:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=mlx.supp ./$(NAME)

.PHONY: all clean fclean re


