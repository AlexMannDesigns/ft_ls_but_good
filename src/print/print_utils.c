#include "ft_ls.h"

static void copy_smaller_chunks(void **dst, void **src, size_t *n)
{
	const unsigned int *s;
	unsigned int *d;

	s = (unsigned int *) *src;
	d = (unsigned int *) *dst;
    while (*n >= sizeof(unsigned int))
    {
        *d++ = *s++;
        *n -= sizeof(unsigned int);
    }
    *dst = (void *) d;
    *src = (void *) s;
	return ;
}

static void copy_chunks(void **dst, void **src, size_t *n)
{
    const uint64_t	*s;
	uint64_t       	*d;

	s = (uint64_t *) *src;
	d = (uint64_t *) *dst;
    while (*n >= sizeof(uint64_t))
    {
        *d++ = *s++;
        *n -= sizeof(uint64_t);
    }
    *dst = (void *) d;
    *src = (void *) s;
    return ;
}

void    *ft_ls_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char *s;
	unsigned char       *d;

	s = (unsigned char *) src;
	d = (unsigned char *) dst;
	if ((!dst || !src) && n > 0)
		return (NULL);
    if ((uintptr_t)d % sizeof(uint64_t) == 0 && (uintptr_t)s % sizeof(uint64_t) == 0)
        copy_chunks((void **) &d, (void **) &s, &n);
    if ((uintptr_t)d % sizeof(unsigned int) == 0 && (uintptr_t)s % sizeof(unsigned int) == 0)
        copy_smaller_chunks((void **) &d, (void **) &s, &n);
    while (n > 0)
	{
		*d++ = *s++;
		n--;
	}
	return (dst);
}

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
    ft_ls_memcpy(state->print_buf + state->buf_idx, str, len);
    state->buf_idx += len;
    return ;
}
