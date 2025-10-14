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

CC = cc -g -Wall -Wextra -Werror
LDFLAGS = -lreadline

INCLUDE = -I include

LIBFT_DIR = survival_lib/
LIBFT = $(LIB_DIR)$(LIBFT_DIR)survivalib.a

#Archivos
PARSING_DIR = parsing/
PARSING_FILES = checker tokenizer tokenizer_command tokenizer_redir tokenizer_utils

UTILS_DIR = utils/
UTILS_FILES = free_commands search_command split_command is_redirection any_has_error handle_heredoc is_builtin get_last_path

BANNER_DIR = print/
BANNER_FILES = banner export_vars

CMD_UTILS_DIR = command_utils/
CMD_UTILS_FILES = utils1 utils2 utils3

SPLIT_UTILS_DIR = split_utils/
SPLIT_UTILS_FILES = utils1 utils2

EXEC_DIR = execution/
EXEC_FILES = echo exit pwd cd env export unset execute signals try_command

ENVIRON_DIR = environment_vars/
ENVIRON_FILES = set_env add_env dict_utils update_env free_env exists_env delete_env env_to_string_list search_env

MAIN = main

SRC_FILES += $(MAIN)
SRC_FILES += $(addprefix $(PARSING_DIR), $(PARSING_FILES))
SRC_FILES += $(addprefix $(UTILS_DIR), $(UTILS_FILES))
SRC_FILES += $(addprefix $(BANNER_DIR), $(BANNER_FILES))
SRC_FILES += $(addprefix $(CMD_UTILS_DIR), $(CMD_UTILS_FILES))
SRC_FILES += $(addprefix $(SPLIT_UTILS_DIR), $(SPLIT_UTILS_FILES))
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
	@mkdir -p $(OBJ_DIR)$(BANNER_DIR)
	@mkdir -p $(OBJ_DIR)$(CMD_UTILS_DIR)
	@mkdir -p $(OBJ_DIR)$(SPLIT_UTILS_DIR)
	@mkdir -p $(OBJ_DIR)$(EXEC_DIR)
	@mkdir -p $(OBJ_DIR)$(ENVIRON_DIR)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(INCLUDE) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)Library created: $@$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | DIRS
	@echo "$(CYAN)Compiling: $<$(DEF_COLOR)"
	@$(CC) -c $< -o $@ $(INCLUDE)

$(LIBFT):
	@make -sC $(LIB_DIR)$(LIBFT_DIR)

clean:
	@echo "$(RED)Cleaning$(DEF_COLOR)"
	@make fclean -sC $(LIB_DIR)$(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Full clean$(DEF_COLOR)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
