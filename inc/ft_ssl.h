#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>

# define DEBUG 1

typedef struct s_command
{
    const char  *name;
    void        (*func)(int, const char**);
}   t_command;

typedef struct s_md5_flags
{
    bool        p;
    bool        q;
    bool        r;
}   t_md5_flags;

typedef struct s_buffer
{
    const char *buffer;
    const char *filename;
    struct s_buffer *next;
}   t_buffer;

typedef struct s_md5_state
{
    uint32_t    h[4];
    uint8_t     data[64];
    uint64_t    bitlen;
}   t_md5_state;

int     ft_strcmp(const char *s1, const char *s2);
size_t  ft_strlen(const char *s);
void    ft_memset(void *b, int c, size_t len);
void    usage(const char **argv);
void    md5(int argc, const char **argv);

#endif
