# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/10 17:16:58 by MP9               #+#    #+#              #
#    Updated: 2026/06/10 17:17:43 by MP9              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc 
CFLAGS	= -Wall -Wextra -Werror -I.

OBJ_DIR	= ../obj/gnl

SRCS	= get_next_line.c get_next_line_utils.c
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