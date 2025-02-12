# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 10:37:23 by oelleaum          #+#    #+#              #
#    Updated: 2025/02/11 10:41:31 by oelleaum         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

#Attention au relink !!
# ajouter les .d comme dependances : pour l'horodotage des fichiers 
# flags : mmd mp
# include ce qu'on appelle des dependances 

NAME = push_swap

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3
INC = -I includes
SRC_DIR = src
OBJ_DIR = obj

#virer debug.c a la fin 
# faire des sous dossiers
SRC_FILES = pb.c \
						get_cheaper_insertion.c \
            get_min_max_index.c \
            get_nodes_to_top.c \
						init.c \
            reverse_rotations.c \
            main.c \
            rotations.c \
						size_3_sort.c \
						my_algo.c \
						swap.c \
            pa.c \
            update_list_infos.c \
            parsing.c \
            utils.c \
            libft.c

OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/,$(OBJ_FILES))

SIZE ?= 10
RUNS ?= 10
LIST = $(shell cat random_ints.txt)

GREEN=\033[32m
RED=\033[31m
RESET=\033[0m

all: $(NAME)

$(NAME): $(OBJ) Makefile
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "compilation successful: $(NAME)"
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c  ./includes/push_swap.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean 
	rm -f $(NAME)

re: fclean all

tests: $(NAME)
	@./tests.sh $(SIZE) $(RUNS) \

test: $(NAME)
	$(shell ./random_ints.sh $(SIZE))
	@echo "=== list used ==="
	@echo $(LIST)
	@echo
	@echo "=== Valgrind Output ==="
	@valgrind --leak-check=full ./push_swap $(LIST) 2>&1 | tail -n 9
	@echo 
	@echo TOTAL_OPS : $(shell ./push_swap $(LIST) | wc -l)
	@if [ "$(shell ./push_swap $(LIST) | ./checker_linux $(SIZE))" = "OK" ]; then \
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

.PHONY: all clean fclean re test
