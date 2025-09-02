# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvarea-k <bvarea-k@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/21 16:22:40 by bvarea-k          #+#    #+#              #
#    Updated: 2025/08/21 16:56:36 by bvarea-k         ###   ########.fr        #
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
LIB_DIR = lib/
OBJ_DIR = obj/

CC = cc -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

INCLUDE = -I include

LIBFT_DIR = survival_lib/
LIBFT = $(LIB_DIR)$(LIBFT_DIR)survivalib.a

#Archivos
PARSING_DIR = parsing/
PARSING_FILES = checker tokenizer tokenizer_utils

UTILS_DIR = utils/
UTILS_FILES = free_commands

EXEC_DIR = execution/
EXEC_FILES = echo exit pwd cd env export unset execute

ENVIRON_DIR = environment_vars/
ENVIRON_FILES = set_env add_env dict_utils update_env free_env exists_env delete_env env_to_string_list

MAIN = main

SRC_FILES += $(MAIN)
SRC_FILES += $(addprefix $(PARSING_DIR), $(PARSING_FILES))
SRC_FILES += $(addprefix $(UTILS_DIR), $(UTILS_FILES))
SRC_FILES += $(addprefix $(EXEC_DIR), $(EXEC_FILES))
SRC_FILES += $(addprefix $(ENVIRON_DIR), $(ENVIRON_FILES))
SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

DIRS:
	@echo "$(MAGENTA)Creating dirs$(DEF_COLOR)"
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(PARSING_DIR)
	@mkdir -p $(OBJ_DIR)$(UTILS_DIR)
	@mkdir -p $(OBJ_DIR)$(EXEC_DIR)
	@mkdir -p $(OBJ_DIR)$(ENVIRON_DIR)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(INCLUDE) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)Library created: $@$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | DIRS
	@echo "$(CYAN)Compiling: $<$(DEF_COLOR)"
	@$(CC) -c $< -o $@ $(INCLUDE)

$(LIBFT):
	make -sC $(LIB_DIR)$(LIBFT_DIR)

clean:
	@echo "$(RED)Cleaning$(DEF_COLOR)"
	@make fclean -sC $(LIB_DIR)$(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Full clean$(DEF_COLOR)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


