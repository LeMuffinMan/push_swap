# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 10:37:23 by oelleaum          #+#    #+#              #
#    Updated: 2025/02/14 12:17:41 by oelleaum         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Attention au relink !!
# 	libft ?
# ajouter les .d comme dependances : pour l'horodotage des fichiers 
# include ce qu'on appelle des dependances 
# flags : mmd mp
# voir pour les echo -e
# VIRER TOUS LES COMMENTAIRES


NAME = push_swap
BONUS_NAME = checker

CC = cc
CFLAGS = -Wall -Werror -Wextra  
INC = -I includes -I libft/include

SRC_DIR = src
OBJ_DIR = obj
BONUS_DIR = bonus

SRC_FILES = push_swap.c \
            my_algo/get_cheaper_insertion.c \
            utils/get_min_max_index.c \
            utils/array_utils.c \
            utils/list_utils.c \
            my_algo/get_nodes_to_top.c \
            init.c \
            ops/reverse_rotations.c \
            ops/rotations.c \
            ops/ops_utils.c \
            my_algo/easy_cases.c \
            my_algo/my_algo.c \
            ops/swap.c \
						ops/push_on_stack.c \
            my_algo/update_list_infos.c \
            utils/utils.c 

BONUS_SRC_FILES = bonus/checker.c \
									bonus/get_next_line.c \
									bonus/get_next_line_utils.c \
									bonus/ops/push_on_stack.c \
									bonus/ops/swap.c \
									bonus/ops/rotations.c \
									bonus/ops/ops_utils.c \
									bonus/ops/reverse_rotations.c

OBJ_FILES = $(SRC_FILES:.c=.o)
BONUS_OBJ_FILES = $(BONUS_SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/,$(OBJ_FILES))
BONUS = $(addprefix $(BONUS_DIR)/,$(BONUS_OBJ_FILES))

# attention wildcards 
LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a
LIBFT_SRC = $(wildcard $(LIBFT_DIR)/*/*.c)
LIBFT_HEADERS = $(wildcard $(LIBFT_DIR)/include/*.h)
LIBFT_OBJ = $(LIBFT_SRC:.c=.o)
LIBFT_FLAGS = -L$(LIBFT_DIR) $(LIBFT_A)

SIZE ?= 100
RUNS ?= 10
LIST = $(shell cat random_ints.txt)

GREEN=\033[32m
RED=\033[31m
RESET=\033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) -o $(NAME)
	@echo 
	@echo -e "$(GREEN)compilation successful ✅ $(NAME)$(RESET)"
	@echo 

$(LIBFT_A): $(LIBFT_SRC) $(LIBFT_HEADERS) libft/Makefile
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c ./includes/push_swap.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

bonus: $(BONUS_NAME)

$(OBJ_DIR)/bonus/%.o: $(BONUS_DIR)/%.c ./bonus/checker.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(BONUS_NAME): $(BONUS_OBJ_FILES) $(LIBFT_A) $(OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ_FILES) $(LIBFT_FLAGS) -o $(BONUS_NAME)
	@echo 
	@echo -e "$(GREEN)compilation successful ✅ $(BONUS_NAME)$(RESET)"
	@echo

clean:
	rm -rf $(OBJ_DIR)/*

bonus_clean:
	rm -rf $(OBJ_DIR)/bonus/*

fclean: clean bonus_clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

tests: all
	@./tests.sh $(SIZE) $(RUNS); \

test: all
	@./random_ints.sh $(SIZE) > random_ints.txt
	@echo "=== Valgrind Output ==="
	@valgrind --leak-check=full ./push_swap $(LIST) 2>&1 | tail -n 9
	@echo 
	@echo "=== list used ==="
	@echo $(LIST)
	@echo
	@echo TOTAL_OPS : $(shell ./push_swap $(LIST) | wc -l)
	@if [ "$(shell ./push_swap $(LIST) | ./checker_linux $(LIST))" = "OK" ]; then \
		echo -e "checker_linux : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "checker_linux : $(RED)KO$(RESET)"; \
	fi
	@echo
	@echo -e "=== parsing tests ==="
	@# Empty input
	@if [ "$(shell ./push_swap | wc -l)" -eq 0 ]; then \
		echo -e "Empty prompt : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Empty prompt : $(RED)KO$(RESET)"; \
	fi
	@# INT_MAX overflow
	@if [ "$(shell ./push_swap 2147483648 1 2>&1)" = "Error" ]; then \
		echo -e "INT_MAX+1 : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "INT_MAX+1 : $(RED)KO$(RESET)"; \
	fi
	@# INT_MIN underflow
	@if [ "$(shell ./push_swap -2147483649 1 2>&1)" = "Error" ]; then \
		echo -e "INT_MIN-1 : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "INT_MIN-1 : $(RED)KO$(RESET)"; \
	fi
	@# LONG_MIN
	@if [ "$(shell ./push_swap -9223372036854775808 1 2>&1)" = "Error" ]; then \
		echo -e "LONG_MIN : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "LONG_MIN : $(RED)KO$(RESET)"; \
	fi
	@# Quoted numbers with spaces (DEVRAIT ÊTRE VALIDE)
	@if [ "$(shell ./push_swap " 2  1    3")" = "sa" ]; then \
		echo -e "Quoted numbers with spaces : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Quoted numbers with spaces : $(RED)KO$(RESET)"; \
	fi
	@# Mixed quoted/unquoted (CORRECTION SYNTAXE)
	@if [ "$(shell ./push_swap "53 54" 5 6 2>&1)" = "Error" ]; then \
		echo -e "Mixed quoted/unquoted : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Mixed quoted/unquoted : $(RED)KO$(RESET)"; \
	fi
	@# Non-integer character
	@if [ "$(shell ./push_swap 54 57 g 15 2>&1)" = "Error" ]; then \
		echo -e "Non-integer character : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Non-integer character : $(RED)KO$(RESET)"; \
	fi
	@# Invalid number format
	@if [ "$(shell ./push_swap 45/85/45/74 2>&1)" = "Error" ]; then \
		echo -e "Invalid number format : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Invalid number format : $(RED)KO$(RESET)"; \
	fi
	@# Duplicate numbers
	@if [ "$(shell ./push_swap 1 2 3 2 2>&1)" = "Error" ]; then \
		echo -e "Duplicate numbers : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Duplicate numbers : $(RED)KO$(RESET)"; \
	fi
	@# Sorted list
	@if [ -z "$(shell ./push_swap 1 2 3 4 5 2>&1)" ]; then \
		echo -e "Sorted list : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Sorted list : $(RED)KO$(RESET)"; \
	fi
	@# Single element (NE DEVRAIT PAS PRODUIRE D'ERROR)
	@if [ "$(shell ./push_swap 42 2>&1)" = "Error" ]; then \
		echo -e "Single element : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Single element : $(RED)KO$(RESET)"; \
	fi
	@# Letters in number
	@if [ "$(shell ./push_swap -2gfd47 1 2>&1)" = "Error" ]; then \
		echo -e "Letters : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Letters : $(RED)KO$(RESET)"; \
	fi

.PHONY: all clean fclean re test tests bonus
