#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <stdio.h>
# include <stdint.h>

typedef struct s_command {
    const char  *name;
    void        (*func)();
} t_command;

typedef struct md5_state {
    uint32_t buffer[64];
} t_md5_block;


void usage(const char **argv);

#endif
