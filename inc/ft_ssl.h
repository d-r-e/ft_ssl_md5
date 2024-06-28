#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <math.h>

# define DEBUG 0

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
    bool        s;
}   t_md5_flags;

typedef struct s_buffer
{
    const char *buffer;
    const char *filename;
    struct s_buffer *next;
}   t_buffer;

typedef struct s_md5_ctx{
    uint32_t    A, B, C, D;
    uint64_t    count;
    uint8_t     buffer[64];
} t_md5_ctx;



int     ft_strcmp(const char *s1, const char *s2);
size_t  ft_strlen(const char *s);
void    ft_memset(void *b, int c, size_t len);
void    ft_memcpy(void *dst, const void *src, size_t len);
void    usage(const char **argv);
void    exec_command(int argc, const char **argv);
const char *md5main(const char *buffer);

#endif
