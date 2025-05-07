
NAME = ft_ls

CC = gcc

INCLUDE_DIR = ./include

LIBFT_DIR = ./libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE_DIR := $(LIBFT_DIR)/include
GNL_INCLUDE_DIR := $(LIBFT_DIR)/get_next_line

SRC_DIR = ./src

SRC_FILES = main.c \
		options/options_control.c options/set_options_control.c options/options_utils.c \
		options/handle_word_options.c options/handle_single_char_option.c \
		error/print_ls_error.c error/print_custom_error.c \
		test/test_utils.c \
		ft_ls_control/ft_ls_control.c ft_ls_control/ft_ls_utils.c ft_ls_control/list_utils.c \
		ft_ls_control/filename_args_control.c ft_ls_control/construct_file_list.c \
		print/print_control.c print/print_linebreak_and_title.c print/print_utils.c \
		print/print_comma_format.c print/print_one_format.c print/print_columns_format.c \
		print/print_buf.c \
		print/print_long/date_and_time.c print/print_long/file_name_and_link.c \
		print/print_long/file_size.c print/print_long/file_type_and_permissions.c \
		print/print_long/get_field_widths.c print/print_long/get_usr_and_grp.c \
		print/print_long/number_of_links.c print/print_long/print_long_format.c \
		print/print_long/user_and_group.c \
		print_debug/print_options_state.c print_debug/print_node_list.c \
		sort/compare_values.c sort/sort_node_list.c sort/sort_filename_args.c \
		utils/string.c

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

