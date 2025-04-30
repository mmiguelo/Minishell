# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yes <yes@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 15:04:25 by frbranda          #+#    #+#              #
#    Updated: 2025/04/30 12:02:15 by yes              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                    NAMES                                     #
#==============================================================================#

CC = cc
FLAGS = -g -Wall -Wextra -Werror
INC = -I./includes
RM = rm -rf

VAL = valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --errors-for-leak-kinds=definite

GENERAL = main.c init.c shell_helper.c
PARSING = parsing.c syntax_error_helper.c syntax_pipes.c syntax_quotes.c syntax_redir.c
TOKENIZER = tokenizer.c token_tools.c \
			token_split_space.c type_helper.c \
			expansion_helper.c handle_dollar_cases.c handle_expansions.c \
			handle_quote.c quote_helper.c \
			add_new_token.c
BUILTIN = builtin_utils.c cd.c cd1.c echo.c env.c exit.c \
			export.c export1.c export2.c export3.c pwd.c unset.c
SIGNAL = signal.c signal_handler.c setget_signo.c
FREE = free.c free_shell.c free_exit.c
ERRORS = print_error.c
PRINT = print_tokens.c
BINARY_TREE = tree.c node.c tree_helper.c exec_tree.c

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

# src
VPATH += src
# free
VPATH += src/00_frees
# errors
VPATH += src/01_errors
# signals
VPATH += src/02_signals
# parsing
VPATH += src/03_parsing
# tokenizer
VPATH += src/04_tokenizer
VPATH += src/04_tokenizer/00_handle_spaces
VPATH += src/04_tokenizer/01_handle_expansions
VPATH += src/04_tokenizer/02_handle_quote
VPATH += src/04_tokenizer/03_add_new_token
# builtin
VPATH += src/builtin
# print
VPATH += src/prints
#binary_tree
VPATH += src/binary_tree/making_tree
VPATH += src/binary_tree/executing_tree

#==============================================================================#
#                                    FILES                                     #
#==============================================================================#

SRC +=	$(GENERAL)
SRC +=	$(FREE)
SRC +=	$(ERRORS)
SRC +=	$(SIGNAL)
SRC +=	$(PARSING)
SRC +=	$(TOKENIZER)
SRC +=	$(BUILTIN)
SRC +=	$(PRINT)
# binary_tree
SRC +=	$(BINARY_TREE)

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
