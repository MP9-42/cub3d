# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/10 17:13:59 by MP9               #+#    #+#              #
#    Updated: 2026/06/19 13:25:39 by alegeber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
BIG_DIR = objs
SRCFILES = srcs/main.c srcs/parsing/colors.c srcs/parsing/map_parse.c srcs/utils/utils1.c \
			srcs/errors/errors1.c srcs/parsing/parser_utils.c \
			srcs/player/player_init.c srcs/raycaster/dda.c \


OBJS = $(SRCFILES:srcs/%.c=$(BIG_DIR)/%.o)
CC = cc
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

CFLAGS = -Wall -Wextra -Werror -I./includes/ -I./libftV2/ -I./gnl/ -I$(MLX_DIR)

RESET = \033[0m
BOLD = \033[1m
BLUE = \033[34m
CYAN = \033[36m
GREEN = \033[32m
YELLOW = \033[33m
PURPLE = \033[35m
RED = \033[31m

WRAPPERS =	-Wl,--wrap=malloc \
			-Wl,--wrap=free \
			-Wl,--wrap=exit

LIBFT_DIR = ./libftV2
LIBFT = $(LIBFT_DIR)/libft.a

GARBAGE_DIR = ./garbage
GARBAGE_SRCS = $(GARBAGE_DIR)/gc.c $(GARBAGE_DIR)/gc_utils.c
GARBAGE_OBJS = $(GARBAGE_SRCS:$(GARBAGE_DIR)/%.c=$(GARBAGE_DIR)/%.o)

GNL_DIR = ./gnl
GNL_SRCS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:$(GNL_DIR)/%.c=$(GNL_DIR)/%.o)

all : $(LIBFT) $(MLX) $(GARBAGE_OBJS) $(GNL_OBJS) $(NAME)

$(NAME): $(OBJS) $(GARBAGE_OBJS) $(GNL_OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(GARBAGE_OBJS) $(GNL_OBJS) $(LIBFT) $(MLX_FLAGS) $(WRAPPERS) -o $(NAME)

$(MLX):
	@$(MAKE) -s --no-print-directory -C $(MLX_DIR)


$(BIG_DIR)/%.o: srcs/%.c includes/cub3d.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -s --no-print-directory -C $(LIBFT_DIR)

$(GARBAGE_DIR)/%.o: $(GARBAGE_DIR)/%.c $(GARBAGE_DIR)/gc.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(GNL_DIR)/%.o: $(GNL_DIR)/%.c $(GNL_DIR)/get_next_line.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BIG_DIR)
	@rm -f $(GARBAGE_OBJS)
	@rm -f $(GNL_OBJS)
	@$(MAKE) -s --no-print-directory clean -C $(LIBFT_DIR) > /dev/null

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s --no-print-directory fclean -C $(LIBFT_DIR) > /dev/null

re:
	@$(MAKE) -s --no-print-directory fclean
	@$(MAKE) -s --no-print-directory all

.PHONY: all clean fclean re
