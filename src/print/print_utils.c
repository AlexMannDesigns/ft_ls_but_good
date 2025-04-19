#include "ft_ls.h"

void    flush_buf(t_ls *state)
{
    write(STDOUT_FILENO, state->print_buf, state->buf_idx);
    state->buf_idx = 0;
    return ;
}

void    add_to_buf(t_ls *state, char *str)
{
    size_t  len;

    len = ft_strlen(str);
    if (state->buf_idx + len + 1 >= BUF_SIZE)
        flush_buf(state);
    ft_memcpy(state->print_buf + state->buf_idx, str, len);
    state->buf_idx += len;
    return ;
}
