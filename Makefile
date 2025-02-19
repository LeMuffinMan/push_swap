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

NAME = push_swap
BONUS_NAME = checker

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 
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
    bonus/src/checker_bonus.c \
    bonus/src/init_bonus.c \
    bonus/src/array_utils_bonus.c \
    bonus/src/lst_utils_bonus.c \
    bonus/src/utils_bonus.c \
    bonus/src/ops/ops_bonus.c \
    bonus/src/ops/execute_ops_bonus.c \
    bonus/src/ops/ops_utils_bonus.c

BONUS_OBJ_FILES = $(addprefix $(BONUS_OBJ_DIR)/, $(subst bonus/src/, , $(BONUS_SRC_FILES:.c=.o)))

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

GREEN=\033[32m
RED=\033[31m
RESET=\033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) Makefile libft/Makefile libft/include/libft.h
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) $(LIBFT_A) -o $(NAME)
	@echo 
	@echo "$(GREEN)compilation successful ✅ $(NAME)$(RESET)"
	@echo 

$(LIBFT_A): $(LIBFT_SRC_FILES) FORCE
	@$(MAKE) --no-print-directory -C libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c ./includes/push_swap.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) $(INC_LIBFT) -c $< -o $@

bonus: $(BONUS_NAME)

$(BONUS_OBJ_DIR)/%.o: bonus/src/%.c ./bonus/include/checker_bonus.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_BONUS) -c $< -o $@

$(BONUS_OBJ_DIR)/ops/%.o: bonus/src/ops/%.c ./bonus/include/checker_bonus.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_BONUS) -c $< -o $@

$(BONUS_NAME): $(BONUS_OBJ_FILES) $(LIBFT_A) ./bonus/include/checker_bonus.h
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

FORCE:
.PHONY: all clean fclean re bonus
