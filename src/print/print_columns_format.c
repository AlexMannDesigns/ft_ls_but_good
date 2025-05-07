#include "ft_ls.h"
#include <sys/ioctl.h>

t_string *allocate_file_names_arr(size_t len)
{
    t_string    *file_names;

    file_names = (t_string *) malloc(sizeof(t_string) * len);
    if (!file_names)
        print_malloc_error_and_exit();
    return (file_names);
}

size_t  get_term_width(void)
{
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return ((size_t) w.ws_col);
}

void    print_filename_col(t_print *print, t_string filename, size_t width)
{
    add_to_buf(print, filename.str, filename.len);
    add_spaces_to_buf(print, width - filename.len);
    return ;
}

/*
 * The column calculation is nice and straightforward, we just divide the width
 * of the terminal by the length of the longest filename. The rows is a little
 * trickier. The calculation is basically the equivalent of:
 *      ceil(num_of_files /num_of_cols)
 * Because C will always round down if the division leaves a remainder. However,
 * we want to round UP and not use the math library.
*/
void    calculate_cols_and_rows(t_print *print, size_t max_len)
{
    print->col_width = max_len + 1;
    print->num_cols = (size_t) (get_term_width() / print->col_width);
    if (print->num_cols == 0)
        print->num_cols = 1;
    print->rows = (size_t) ((print->list_len + print->num_cols - 1) / print->num_cols);
    return ;
}

/*
 * Prints a list of filenames in a multi-column layout.
 *
 * The filenames are arranged in the selected sorting order *down* each
 * column, but printing is performed *across* rows (left to right), to
 * match traditional `ls` behavior.
 *
 * The array `file_names` holds all entries, and is indexed to avoid
 * repeated traversal. Each row iterates across all columns, calculating
 * the index for each column using: index = row + (col * total_rows).
 *
 * For each valid index, a filename is printed with column-aligned padding.
 * After each row is complete, a newline is added to the output buffer.
 *
 * Parameters:
 * - print: holds metadata like number of rows, columns, column width, etc.
 * - files_arr: array of filenames and their lengths, sorted.
 */
void    print_columns(t_print *print, t_string *files_arr)
{
    size_t row;
    size_t col;
    size_t index;

    row = 0;
    while (row < print->rows)
    {
        col = 0;
        while (col < print->num_cols)
        {
            index = row + (col * print->rows);
            if (index < print->list_len)
                print_filename_col(print, files_arr[index], print->col_width);
            col++;
        }
        add_nl_to_buf(print);
        row++;
    }
    return ;
}

size_t  get_max_len_and_populate_file_names(t_list *files, t_string *files_arr)
{
    t_list      *iter;
    t_file_info *current;
    size_t      i;
    size_t      max_len;

    max_len = 0;
    i = 0;
    iter = files;
    while (iter)
    {
        current = (t_file_info *) iter->content;
        if (current->path.len > max_len)
            max_len = current->path.len;
        files_arr[i] = current->path;
        i++;
        iter = iter->next;
    }
    return (max_len);
}

/*
 * To print neatly aligned columns, we follow a three-step process:
 *
 * 1. Scan the input list once to determine the longest file name. While doing
 *    so, we populate an array of (string, length) pairs for efficient random
 *    access.
 *
 * 2. Use the maximum filename length and the terminal width to calculate the
 *    optimal number of columns and rows.
 *
 * 3. Use a row-by-row column-printing algorithm to display the entries in
 *    lexicographic order *down* each column, while printing line-by-line
 *    *across* the rows.
 *
 * This layout strategy avoids repeated list traversal and ensures optimal
 * spacing.
 */
void    print_columns_format(t_ls *state, t_list *files)
{
    t_string    *files_arr;
    size_t      max_len;

    files_arr = allocate_file_names_arr(state->print.list_len);
    max_len = get_max_len_and_populate_file_names(files, files_arr);
    calculate_cols_and_rows(&(state->print), max_len);
    print_columns(&(state->print), files_arr);
    free(files_arr);
    return ;
}
