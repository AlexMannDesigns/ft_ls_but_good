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

# define BUF_SIZE 4096

# define OPTIONS "RSalmnrt1"
# define USAGE "usage: ./ft_ls [-RSalmnrt] [file ...]"
# define TEST "--TEST"

# define ERROR_FILETYPE "Error: could not find matching file-type, exiting..."

# define RWX_CHARS "rwxrwxrwx"

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
    COLUMNS = 0,
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
}                   t_options;

typedef struct s_print
{
    char            *print_buf;
    size_t          buf_index;
    unsigned int    print_newline;
    unsigned int    printing_file_args;
    unsigned int    link_width;
    unsigned int    user_width;
    unsigned int    group_width;
    unsigned int    size_width;
}                   t_print;

typedef struct s_ls
{
    t_options       options;
    t_print         print;
    size_t          argv_index;
    unsigned int    remaining_argv_len;
    unsigned int    testing;
    t_list          *directories;
    t_list          *regular_files;
}                   t_ls;


/*** Typedefs ***/

typedef int     (*t_option_handler)(t_options *, char);
typedef void    (*t_print_format)(t_ls *, t_list *);


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
unsigned char   get_file_type_char(mode_t st_mode);

/* list_utils.c */
void            add_node_to_list(t_list **list, char *filename, struct stat sys_file_info);
void            free_node_list(t_list **list);
void            cleanup_lists_and_print_buf(t_ls *state);


/* PRINT */

/* print_comma_format.c */
void            print_comma_format(t_ls *state, t_list *current);

/* print_one_format.c */
void            print_one_format(t_ls *state, t_list *current);

/* print_columns_format.c */
void            print_columns_format(t_ls *state, t_list *current);

/* print_long_format.c */
void            print_long_format(t_ls *state, t_list *current);

/* print_control.c */
void            print_control(t_ls *state, t_list *files);

/* print_options_state.c */
void            print_options_state_and_exit(t_ls state);

/* print_linebreak_and_title.c */
void            print_linebreak_and_title(t_ls *state, char *directory_name);

/* print_utils.c */
int             file_should_be_printed(t_ls *state, char *path);
void            add_to_buf(t_print *print, char *str);
void            add_to_buf_len(t_print *print, char *str, size_t len);
void            flush_buf(t_print *print);
void            add_spaces_to_buf(t_print *print, size_t spaces);


/* SORT */

/* compare_values.c */
unsigned int    compare_values(t_options options, t_file_info *a, t_file_info *b);

/* sort_node_list.c */
void            sort_node_list(t_options options, t_list **list);

/* sort_filename_args.c */
void            sort_filename_args(char **args);


/* TEST */

/* test_utils.c */
unsigned int    check_testing(int argc, char **argv);

# endif
