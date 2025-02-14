# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 15:04:25 by frbranda          #+#    #+#              #
#    Updated: 2025/02/12 13:39:56 by frbranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#==============================================================================#
#                                    NAMES                                     #
#==============================================================================#

CC = cc
FLAGS = -g -Wall -Wextra -Werror
INC = -I./includes
RM = rm -rf

GENERAL = main.c
TOKEN = tokenizer.c free_tokens.c

VAL = valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --errors-for-leak-kinds=definite

NAME = minishell

#==============================================================================#
#                                    EXTRA                                     #
#==============================================================================#

ECHO = @echo
GREEN = \033[1;32m
RED = \033[1;31m
RESET = \033[0m

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

VPATH += src
VPATH += src/tokens

#==============================================================================#
#                                    FILES                                     #
#==============================================================================#

SRC +=	$(GENERAL)
SRC +=	$(TOKEN)

# Library Paths
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Objects Paths
OBJ_DIR = obj
OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

#==============================================================================#
#                                    RULES                                     #
#==============================================================================#

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@$(ECHO) "$(GREEN)----------------- minishell created$(RESET)"

# Make and run
r: all
	./minishell

# Make and run with valgrind
rv: all
	$(VAL) ./minishell

# Executable minishell with valgrind
v: re
	$(VAL) ./minishell

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(RED)----------------- OBJECTS deleted$(RESET)"

fclean: clean
	$(RM) $(NAME) $(OBJ_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)----------------- minishell deleted$(RESET)"

re: fclean all

# Phony Targets
.PHONY: all clean fclean re
