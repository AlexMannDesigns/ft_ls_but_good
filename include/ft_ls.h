
#ifndef FT_LS_H
# define FT_LS_H


/*** Predefined values ***/
    
# define TRUE 1
# define FALSE 0

# define OPTIONS "RSalmnrt1"
# define USAGE "usage: ./ft_ls [-RSalmnrt] [file ...]"
# define TEST "--TEST"


/*** Enums ***/

typedef enum e_display
{
    COLUMNS,
    LONG,
    COMMA,
    ONE,
}   t_display;

typedef enum e_sort
{
    LEXICOGRAPHICAL,
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

typedef struct s_options
{
    t_display       display;
    t_sort          sort;
    unsigned int    misc;
}   t_options;

typedef struct s_ls
{
    t_options       options;
    unsigned int    argv_index;
    unsigned int    testing;
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

/* print_error.c */
void            print_options_error(char options);
void            print_unrecognized_option_error(char *arg);
void            print_valid_option_not_handled_error(char option);

/* PRINT */

/* print_options_state.c */
void            print_options_state(t_ls state);


/* TEST */

/* test_utils.c */
unsigned int    check_testing(int argc, char **argv);

# endif
