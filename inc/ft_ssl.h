#ifndef FT_SSL_H
# define FT_SSL_H

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>

#define BUFFER_SIZE 4096

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

//* MD5 *//
void    md5main(const t_buffer *buffer, t_md5_flags flags);
void md5file(const t_buffer *file_buffer, t_md5_flags flags);

//* SHA256 *//


#endif
