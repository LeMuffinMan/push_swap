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
            utils.c

OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/,$(OBJ_FILES))

RANDOM_NUMBERS = $(shell cat random_ints.txt)
PUSH_SWAP_OUTPUT = $(shell ./push_swap $(RANDOM_NUMBERS))

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

test: $(NAME) 
	@echo "=== parsing tests ==="
	@if [ "$(shell ./push_swap | wc -l)" -eq 0 ]; then \
    echo "Empty prompt : OK"; \
  else \
  echo "Empty prompt : KO"; \
  fi
	@if [ "$(shell ./push_swap 2147483648 1)" = "Error" ]; then \
		echo "INT_MAX : OK"; \
	else \
	echo "INT_MAX : KO"; \
	fi	
	@if [ "$(shell ./push_swap -2147483649 1)" = "Error" ]; then \
		echo "INT_MIN : OK"; \
	else \
	echo "INT_MIN : KO"; \
	fi	
	@if [ "$(shell ./push_swap -21474fd83647 1)" = "Error" ]; then \
		echo "Letters : OK"; \
	else \
	echo "letters : KO"; \
	fi	
	@echo "=== list used ==="
	@echo $(RANDOM_NUMBERS)
	@echo
	@echo "=== Valgrind Output ==="
	@valgrind --leak-check=full ./push_swap $(RANDOM_NUMBERS) 2>&1 | tail -n 9
	@echo 
	@echo "=== COUNT ===" 
	@echo "RA : $(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "ra") ($(shell echo "scale=2; 100*$(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "ra")/$(shell ./push_swap $(RANDOM_NUMBERS) | wc -l)" | bc)%)"
	@echo "RB : $(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "rb") ($(shell echo "scale=2; 100*$(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "rb")/$(shell ./push_swap $(RANDOM_NUMBERS) | wc -l)" | bc)%)"
	@echo "RR : $(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "rr") ($(shell echo "scale=2; 100*$(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "rr")/$(shell ./push_swap $(RANDOM_NUMBERS) | wc -l)" | bc)%)"
	@echo "RRA : $(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "rra") ($(shell echo "scale=2; 100*$(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "rra")/$(shell ./push_swap $(RANDOM_NUMBERS) | wc -l)" | bc)%)"
	@echo "RRB : $(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "rrb") ($(shell echo "scale=2; 100*$(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "rrb")/$(shell ./push_swap $(RANDOM_NUMBERS) | wc -l)" | bc)%)"
	@echo "RRR : $(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "rrr") ($(shell echo "scale=2; 100*$(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "rrr")/$(shell ./push_swap $(RANDOM_NUMBERS) | wc -l)" | bc)%)"
	@echo "SA : $(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "sa") ($(shell echo "scale=2; 100*$(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "sa")/$(shell ./push_swap $(RANDOM_NUMBERS) | wc -l)" | bc)%)"
	@echo "SB : $(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "sb") ($(shell echo "scale=2; 100*$(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "sb")/$(shell ./push_swap $(RANDOM_NUMBERS) | wc -l)" | bc)%)"
	@echo "SS : $(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "ss") ($(shell echo "scale=2; 100*$(shell ./push_swap $(RANDOM_NUMBERS) | grep -c "ss")/$(shell ./push_swap $(RANDOM_NUMBERS) | wc -l)" | bc)%)"
	@echo
	@echo TOTAL_OPS : $(shell ./push_swap $(RANDOM_NUMBERS) | wc -l)
	@echo "checker_linux : $(shell ./push_swap $(RANDOM_NUMBERS) | ./checker_linux $(RANDOM_NUMBERS))"
	@echo

.PHONY: all clean fclean re test
