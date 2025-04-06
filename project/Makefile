# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saru <saru@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/19 01:21:19 by zsonie            #+#    #+#              #
#    Updated: 2025/04/06 19:29:29 by saru             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client
SERVER = server

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC_CLIENT = client.c
SRC_SERVER = server.c \
			ft_itoa.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

all: $(CLIENT) $(SERVER)

$(CLIENT): $(OBJ_CLIENT)
	@echo "$(GREEN)Compile $(CLIENT)$(RESET)"
	@$(CC) $(CFLAGS) -o $(CLIENT) $(OBJ_CLIENT)

$(SERVER): $(OBJ_SERVER)
	@echo "$(GREEN)Compile $(SERVER)$(RESET)"
	@$(CC) $(CFLAGS) -o $(SERVER) $(OBJ_SERVER)

clean:
	@echo "$(RED)Remove $(GREEN)$(OBJ_CLIENT) $(RED)and $(GREEN)$(OBJ_SERVER)$(RED) files.$(RESET)"
	@$(RM) $(OBJ_CLIENT) $(OBJ_SERVER)

fclean: clean
	@echo "$(RED)Remove $(GREEN)$(CLIENT) $(RED)and $(GREEN)$(SERVER)$(RED) executables.$(RESET)"
	@$(RM) $(CLIENT) $(SERVER)

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                  Colors                                      #
# **************************************************************************** #

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m
