
NAME = ft_ls

CC = gcc

INCLUDE_DIR = ./include

LIBFT_DIR = ./libft
LIBFT := $(LIBFT_DIR)/libft.a 
LIBFT_INCLUDE_DIR := $(LIBFT_DIR)/include
GNL_INCLUDE_DIR := $(LIBFT_DIR)/get_next_line

SRC_DIR = ./src

SRC_FILES = main.c options/options_control.c options/set_options_control.c options/options_utils.c \
		options/handle_word_options.c options/handle_single_char_option.c error/print_ls_error.c \
		error/print_custom_error.c print/print_options_state.c test/test_utils.c ft_ls_control/ft_ls_control.c

OBJ_DIR = ./obj
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(SRC_FILES:.c=.o))

GCC_FLAGS = -Wall -Wextra -Werror -g

LIBFT_FLAGS := -L"$(LIBFT_DIR)" -lft

INCLUDE_FLAGS := -I$(INCLUDE_DIR) -I$(LIBFT_INCLUDE_DIR) -I$(GNL_INCLUDE_DIR) 

#################################################################

	
##### FT_LS RECIPES #####

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(GCC_FLAGS) $(OBJS) -o $(NAME) $(LIBFT_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(GCC_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all


##### LIBRARY RECIPES #####

$(LIBFT):
	make -C $(LIBFT_DIR)

libft_clean:
	make -C $(LIBFT_DIR) clean

libft_fclean: libft_clean
	make -C $(LIBFT_DIR) fclean


##### RECIPES FOR ALL #####

fclean_all: fclean libft_fclean 

.PHONY: all clean fclean re libft

