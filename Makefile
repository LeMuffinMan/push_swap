# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 10:37:23 by oelleaum          #+#    #+#              #
#    Updated: 2025/02/15 17:44:45 by oelleaum         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# supprimer split ?
# mettre es bonus a la norme 
# tout avec _bonus
# n'est pas suppose se conneter a push_swap.h ?
# retenter de bien ranger les obj bonus ?

# incertain !
# ▶ ARG="1   2 3"; ./push_swap $ARG
# Error

NAME = push_swap
BONUS_NAME = checker

CC = cc
CFLAGS = -Wall -Werror -Wextra  
INC = -I includes
INC_LIBFT = -I libft/include
INC_BONUS = -I bonus/include

SRC_DIR = src
OBJ_DIR = obj

LIBFT_SRC_DIR = libft/src
LIBFT_OBJ_DIR = libft/obj
BONUS_SRC_DIR = bonus/src
BONUS_OBJ_DIR = bonus/obj

LIBFT_SRC_FILES = \
    libft/src/ft_atoi.c \
    libft/src/ft_bzero.c \
    libft/src/ft_calloc.c \
    libft/src/ft_isalnum.c \
    libft/src/ft_isalpha.c \
    libft/src/ft_isascii.c \
    libft/src/ft_isdigit.c \
    libft/src/ft_isprint.c \
    libft/src/ft_itoa.c \
    libft/src/ft_lstadd_back_bonus.c \
    libft/src/ft_lstadd_front_bonus.c \
    libft/src/ft_lstclear_bonus.c \
    libft/src/ft_lstdelone_bonus.c \
    libft/src/ft_lstiter_bonus.c \
    libft/src/ft_lstlast_bonus.c \
    libft/src/ft_lstnew_bonus.c \
    libft/src/ft_lstsize_bonus.c \
    libft/src/ft_memchr.c \
    libft/src/ft_memcmp.c \
    libft/src/ft_memcpy.c \
    libft/src/ft_memmove.c \
    libft/src/ft_memset.c \
    libft/src/ft_putchar_fd.c \
    libft/src/ft_putendl_fd.c \
    libft/src/ft_putnbr_fd.c \
    libft/src/ft_putstr_fd.c \
    libft/src/ft_split.c \
    libft/src/ft_strdup.c \
    libft/src/ft_strchr.c \
    libft/src/ft_striteri.c \
    libft/src/ft_strjoin.c \
    libft/src/ft_strlcat.c \
    libft/src/ft_strlcpy.c \
    libft/src/ft_strmapi.c \
    libft/src/ft_strnstr.c \
    libft/src/ft_strrchr.c \
    libft/src/ft_strtrim.c \
    libft/src/ft_substr.c \
    libft/src/ft_strlen.c \
    libft/src/ft_strncmp.c \
    libft/src/ft_tolower.c \
    libft/src/ft_toupper.c \
    libft/src/ft_split.c \
    libft/src/get_next_line.c \
    libft/src/get_next_line_utils.c


LIBFT_OBJ_FILES = $(LIBFT_SRC_FILES:.c=.o)

BONUS_SRC_FILES = \
    bonus/src/checker.c \
    bonus/src/init.c \
    bonus/src/array_utils.c \
    bonus/src/lst_utils.c \
    bonus/src/utils.c \
    bonus/src/ops/ops.c \
    bonus/src/ops/execute_ops.c \
    bonus/src/ops/ops_utils.c 

BONUS_OBJ_FILES = $(BONUS_SRC_FILES:.c=.o)

SRC_FILES = \
    push_swap.c \
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

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR)/,$(OBJ_FILES))
BONUS = $(addprefix $(BONUS_OBJ_DIR)/,$(BONUS_OBJ_FILES))

LIBFT_A = libft/libft.a

SIZE ?= 100
RUNS ?= 100
TARGET ?= 700
LIST = $(shell cat random_ints.txt)

GREEN=\033[32m
RED=\033[31m
RESET=\033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) $(LIBFT_A) -o $(NAME)
	@echo 
	@echo "$(GREEN)compilation successful ✅ $(NAME)$(RESET)"
	@echo 

$(LIBFT_A): $(LIBFT_SRC_FILES)
	@$(MAKE) --no-print-directory -C libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c ./includes/push_swap.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) $(INC_LIBFT) -c $< -o $@

bonus: $(BONUS_NAME)

$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c ./bonus/include/checker.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_BONUS) -c $< -o $@

$(BONUS_NAME): $(BONUS_OBJ_FILES) $(LIBFT_A) $(OBJ) ./bonus/include/checker.h 
	$(CC) $(CFLAGS) $(BONUS_OBJ_FILES) $(LIBFT_A) $(LIBFT_FLAGS) -o $(BONUS_NAME)
	@echo 
	@echo "$(GREEN)compilation successful ✅ $(BONUS_NAME)$(RESET)"
	@echo

clean:
	rm -rf $(OBJ_DIR)/*

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	rm -f $(LIBFT_A)

re: fclean all

#a virer !!!!
tests: all
	@./tests.sh $(SIZE) $(RUNS); \

test: all
	@./random_ints.sh $(SIZE) > random_ints.txt
	@echo "=== list used ==="
	@echo $(LIST)
	@echo
	@echo "=== Valgrind Output ==="
	@valgrind --leak-check=full ./push_swap $(LIST) 2>&1 | tail -n 9
	@echo 
	@echo TOTAL_OPS : $(shell ./push_swap $(LIST) | wc -l)
	@if [ "$(shell ./push_swap $(LIST) | ./checker_linux $(LIST))" = "OK" ]; then \
		echo "checker_linux : $(GREEN)OK$(RESET)"; \
	else \
		echo "checker_linux : $(RED)KO$(RESET)"; \
	fi
	@echo
	@echo "=== parsing tests ==="
	@# Empty input
	@if [ "$(shell ./push_swap | wc -l)" -eq 0 ]; then \
		echo "Empty prompt : $(GREEN)OK$(RESET)"; \
	else \
		echo "Empty prompt : $(RED)KO$(RESET)"; \
	fi
	@# INT_MAX overflow
	@if [ "$(shell ./push_swap 2147483648 1 2>&1)" = "Error" ]; then \
		echo "INT_MAX+1 : $(GREEN)OK$(RESET)"; \
	else \
		echo "INT_MAX+1 : $(RED)KO$(RESET)"; \
	fi
	@# INT_MIN underflow
	@if [ "$(shell ./push_swap -2147483649 1 2>&1)" = "Error" ]; then \
		echo "INT_MIN-1 : $(GREEN)OK$(RESET)"; \
	else \
		echo "INT_MIN-1 : $(RED)KO$(RESET)"; \
	fi
	@# LONG_MIN
	@if [ "$(shell ./push_swap -9223372036854775808 1 2>&1)" = "Error" ]; then \
		echo "LONG_MIN : $(GREEN)OK$(RESET)"; \
	else \
		echo "LONG_MIN : $(RED)KO$(RESET)"; \
	fi
	@# Quoted numbers with spaces (DEVRAIT ÊTRE VALIDE)
	@if [ "$(shell ./push_swap  2  1    3)" = "sa" ]; then \
		echo "Quoted numbers with spaces : $(GREEN)OK$(RESET)"; \
	else \
		echo "Quoted numbers with spaces : $(RED)KO$(RESET)"; \
	fi
	@# Mixed quoted/unquoted (CORRECTION SYNTAXE)
	@if [ "$(shell ./push_swap "53 54" 5 6 2>&1)" = "Error" ]; then \
		echo "Mixed quoted/unquoted : $(GREEN)OK$(RESET)"; \
	else \
		echo "Mixed quoted/unquoted : $(RED)KO$(RESET)"; \
	fi
	@# Non-integer character
	@if [ "$(shell ./push_swap 54 57 g 15 2>&1)" = "Error" ]; then \
		echo "Non-integer character : $(GREEN)OK$(RESET)"; \
	else \
		echo "Non-integer character : $(RED)KO$(RESET)"; \
	fi
	@# Invalid number format
	@if [ "$(shell ./push_swap 45/85/45/74 2>&1)" = "Error" ]; then \
		echo "Invalid number format : $(GREEN)OK$(RESET)"; \
	else \
		echo "Invalid number format : $(RED)KO$(RESET)"; \
	fi
	@# Duplicate numbers
	@if [ "$(shell ./push_swap 1 2 3 2 2>&1)" = "Error" ]; then \
		echo "Duplicate numbers : $(GREEN)OK$(RESET)"; \
	else \
		echo "Duplicate numbers : $(RED)KO$(RESET)"; \
	fi
	@# Sorted list
	@if [ -z "$(shell ./push_swap 1 2 3 4 5 2>&1)" ]; then \
		echo "Sorted list : $(GREEN)OK$(RESET)"; \
	else \
		echo "Sorted list : $(RED)KO$(RESET)"; \
	fi
	@# Single element 
	@if [ -z "$(shell ./push_swap 42 2>&1)" ]; then \
		echo "Single element : $(GREEN)OK$(RESET)"; \
	else \
		echo "Single element : $(RED)KO$(RESET)"; \
	fi
	@# Letters in number
	@if [ "$(shell ./push_swap -2gfd47 1 2>&1)" = "Error" ]; then \
		echo "Letters : $(GREEN)OK$(RESET)"; \
	else \
		echo "Letters : $(RED)KO$(RESET)"; \
	fi
	@echo ''

leaks: all
	@echo "=== Leaks ==="
	@./leaks_check.sh
	@if [ "$$(grep -c 'failed' logs/valgrind_output.txt)" -gt 0 ]; then \
    echo ''; \
    echo '$(RED)LEAKS KO !$(RESET)'; \
    echo 'logs/valgrind_output.txt'; \
    echo ''; \
    grep 'failed' logs/valgrind_output.txt; \
	else \
    echo ''; \
    echo '$(GREEN)No leaks, but better to$(RESET) $(RED)double check !$(RESET)'; \
    echo ''; \
	fi

complexity: all
	@echo "=== Perf test ==="
	@./complexity $(SIZE) $(RUNS) $(TARGET) ./checker_linux

all_tests: all test leaks 
	@echo "=== Perf test ==="
	@./complexity 100 100 700 ./checker_linux
	@echo ''
	@./complexity 500 100 5500 ./checker_linux


.PHONY: all clean fclean re bonus
