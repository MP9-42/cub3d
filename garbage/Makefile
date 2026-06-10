# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/08 21:35:47 by MP9               #+#    #+#              #
#    Updated: 2026/04/08 22:01:52 by MP9              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc 
CFLAGS	= -Wall -Wextra -Werror -I.

OBJ_DIR	= ../obj/gc

SRCS	= gc.c gc_utils.c
OBJS	= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(OBJS)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)


fclean: clean

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re