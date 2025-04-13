
#ifndef FT_LS_H
# define FT_LS_H

/*** Header files ***/

/* for the stat struct */
# include <sys/stat.h>

/* for t_list struct */
# include "libft.h"

/*** Predefined values ***/
    
# define TRUE 1
# define FALSE 0

# define OPTIONS "RSalmnrt1"
# define USAGE "usage: ./ft_ls [-RSalmnrt] [file ...]"
# define TEST "--TEST"


/*** Enums ***/

typedef enum e_file_type
{
    FIFO,
    CHAR,
    DIRECTORY,
    BLOCK,
    REGULAR,
    LINK,
    SOCKET,
    WHITEOUT,
}   t_file_type;

typedef enum e_display
{
    COLUMNS,
    LONG,
    COMMA,
    ONE,
}   t_display;

typedef enum e_sort
{
    LEXICOGRAPHICAL = 0,
    TIME,
    SIZE,
}   t_sort;

typedef enum e_misc_bits
{
    RECURSIVE = 0,
    REVERSED,
    ALL,
}   t_misc_bits;


/*** Structs ***/

typedef struct s_print
{
    unsigned int    print_newline;
    unsigned int    print_title;
    unsigned int    printing_directory;
    char            *directory_name;
}   t_print;

typedef struct s_file_info
{
    char            *command_line;
    char            *path;
    struct stat     sys_file_info;
}                   t_file_info;

typedef struct s_options
{
    t_display       display;
    t_sort          sort;
    unsigned int    misc;
}   t_options;

typedef struct s_ls
{
    t_options       options;
    t_print         print;
    unsigned int    argv_index;
    unsigned int    remaining_argv_len;
    unsigned int    testing;
    t_list          *directories;
    t_list          *regular_files;
}                   t_ls;


/*** Typedefs ***/

typedef int (*t_option_handler)(t_options *, char);


/*** Functions ***/

/* OPTIONS */

/* handle_word_options.c */
int             handle_word_options(t_ls *state, char *arg);

/* handle_single_char_options.c */
void            handle_single_char_option(t_options *options, char option);

/* options_control.c */
int             options_control(t_ls *state, char **argv);

/* options_utils.c */
int             set_option_value(unsigned int *option, unsigned int value);
int             set_misc_option_bit(unsigned int *misc, unsigned int bit);
int             check_misc_option_bit(unsigned int misc, unsigned int bit);

/* set_options_control.c */
int             set_options_control(t_ls *state, char *arg);


/* ERROR */

/* print_ls_error.c */
void            print_options_error(char options);
void            print_unrecognized_option_error(char *arg);
void            print_filename_error(char *filename);

/* print_custom_error.c */
void            print_valid_option_not_handled_error(char option);
void            print_malloc_error_and_exit(void);
void            print_stat_error_and_exit(char *path);

/* print_invalid_args.c */
void            print_invalid_args(char ***invalid_args);


/* FT_LS_CONTROL */

/* construct_file_list.c */
t_list          *construct_file_list(t_file_info *dir_info);

/* filename_args_control.c */
void            filename_args_control(t_ls *state, char **argv);

/* ft_ls_control.c */
void            ft_ls_control(t_ls *state, char **argv);

/* ft_ls_utils.c */
unsigned int    get_file_type(mode_t st_mode);

/* list_utils.c */
void            add_node_to_list(t_list **list, char *filename, struct stat sys_file_info);
void            free_node_list(t_list **list);
void            cleanup_lists(t_ls *state);

/* sort_node_list.c */
void            sort_node_list(t_options options, t_list **list);

/* sort_filename_args.c */
void            sort_filename_args(char **args);

/* PRINT */

/* print_control.c */
void            print_control(t_ls *state, t_list *files);

/* print_options_state.c */
void            print_options_state_and_exit(t_ls state);


/* TEST */

/* test_utils.c */
unsigned int    check_testing(int argc, char **argv);

# endif
