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


# bien checker : 
# valgrind ./push_swap 1 0 1
# valgrind ./push_swap 1
# cas d'erreur pour une seule valeur envoyee 
# supprimer split ?
# rallonger mon testeur pour tester SYSTEMATIQUEMENT les leaks
# mettre es bonus a la norme 
# tout avec _bonus
# n'est pas suppose se conneter a push_swap.h ?
# retenter de bien ranger les obj bonus ?

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
RUNS ?= 10
LIST = $(shell cat random_ints.txt)

GREEN=\033[32m
RED=\033[31m
RESET=\033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) Makefile ./includes/push_swap.h
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) $(LIBFT_A) -o $(NAME)
	@echo 
	@echo -e "$(GREEN)compilation successful ✅ $(NAME)$(RESET)"
	@echo 

$(LIBFT_A): $(LIBFT_SRC_FILES) libft/Makefile ./libft/include/libft.h
	@$(MAKE) --no-print-directory -C libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c ./includes/push_swap.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) $(INC_LIBFT) -c $< -o $@

bonus: $(BONUS_NAME)

$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c ./bonus/include/checker.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_BONUS) -c $< -o $@

$(BONUS_NAME): $(BONUS_OBJ_FILES) $(LIBFT_A) $(OBJ) ./bonus/include/checker.h Makefile
	$(CC) $(CFLAGS) $(BONUS_OBJ_FILES) $(LIBFT_A) $(LIBFT_FLAGS) -o $(BONUS_NAME)
	@echo 
	@echo -e "$(GREEN)compilation successful ✅ $(BONUS_NAME)$(RESET)"
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

test_leaks_parsing:
	@./leaks_check.sh
	@if [ "$(shell cat logs/valgrind_output.txt | grep "Test failed" | wc -l)" -gt 0 ]; then \
		echo -e "Leaks on parsing : '$(shell awk '/Test failed/' logs/valgrind_output.txt)'"; \
	fi

test: all
	@./random_ints.sh $(SIZE) > random_ints.txt
	@echo "=== Valgrind Output ==="
	@valgrind --leak-check=full ./push_swap $(LIST) 2>&1 | tail -n 9
	@echo 
	@echo "=== list used ==="
	@echo $(LIST)
	@echo
	@echo -e "=== parsing tests ==="
	@if [ "$(shell ./push_swap | wc -l)" -eq 0 ]; then \
		echo -e "Empty prompt : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Empty prompt : $(RED)KO$(RESET)"; \
	fi
	@if [ "$(shell ./push_swap 2147483648 1 2>&1)" = "Error" ]; then \
		echo -e "INT_MAX+1 : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "INT_MAX+1 : $(RED)KO$(RESET)"; \
	fi
	@if [ "$(shell ./push_swap -2147483649 1 2>&1)" = "Error" ]; then \
		echo -e "INT_MIN-1 : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "INT_MIN-1 : $(RED)KO$(RESET)"; \
	fi
	@if [ "$(shell ./push_swap -9223372036854775808 1 2>&1)" = "Error" ]; then \
		echo -e "LONG_INT : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "LONG_INT : $(RED)KO$(RESET)"; \
	fi
	@if [ "$(shell ./push_swap "53 54" 5 6 2>&1)" = "Error" ]; then \
		echo -e "Mixed quoted/unquoted : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Mixed quoted/unquoted : $(RED)KO$(RESET)"; \
	fi
	@if [ "$(shell ./push_swap 54 57 g 15 2>&1)" = "Error" ]; then \
		echo -e "Non-integer character : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Non-integer character : $(RED)KO$(RESET)"; \
	fi
	@if [ "$(shell ./push_swap 45/85/45/74 2>&1)" = "Error" ]; then \
		echo -e "Invalid number format : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Invalid number format : $(RED)KO$(RESET)"; \
	fi
	@if [ "$(shell ./push_swap 1 2 3 2 2>&1)" = "Error" ]; then \
		echo -e "Duplicate numbers : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Duplicate numbers : $(RED)KO$(RESET)"; \
	fi
	@if [ -z "$(shell ./push_swap 1 2 3 4 5 2>&1)" ]; then \
		echo -e "Sorted list : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Sorted list : $(RED)KO$(RESET)"; \
	fi
	@if [ -z "$(shell ./push_swap 42 2>&1)" ]; then \
		echo -e "Single element : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Single element : $(RED)KO$(RESET)"; \
	fi
	@if [ "$(shell ./push_swap -2gfd47 1 2>&1)" = "Error" ]; then \
		echo -e "Letters : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "Letters : $(RED)KO$(RESET)"; \
	fi
	@echo
	@echo TOTAL_OPS : $(shell ./push_swap $(LIST) | wc -l)
	@if [ "$(shell ./push_swap $(LIST) | ./checker_linux $(LIST))" = "OK" ]; then \
		echo -e "checker_linux : $(GREEN)OK$(RESET)"; \
	else \
		echo -e "checker_linux : $(RED)KO$(RESET)"; \
	fi

.PHONY: all clean fclean re bonus
