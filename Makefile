# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/21 16:22:40 by bvarea-k          #+#    #+#              #
#    Updated: 2025/08/21 16:47:50 by bvarea-k         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

#Colores
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRC_DIR = src/
OBJ_DIR = obj/

AR = ar rcs
CC = cc -Wall -Wextra -Werror -g

INCLUDE = -I include

#Archivos
PARSING_DIR = parsing/
PARSING_FILES = checker parser

SRC_FILES += $(addprefix $(PARSING_DIR), $(PARSING_FILES))
SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))


DIRS:
	@echo "$(MAGENTA)Creating dirs$(DEF_COLOR)"
	@mkdir -p $(OBJ_DIR)
	
	all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^
	@echo "$(GREEN)Library created: $@$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | DIRS
	@echo "$(CYAN)Compiling: $<$(DEF_COLOR)"
	@$(CC) -c $< -o $@ $(INCLUDE)
	
clean:
	@echo "$(RED)Cleaning$(DEF_COLOR)"
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)

.PHONY: all clean
