#ifndef FT_SSL_H
#define FT_SSL_H

#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define BUFFER_SIZE 4096

typedef struct s_command {
	const char *name;
	void (*func)(int, const char **);
} t_command;

typedef struct s_md5_flags {
	bool p;
	bool q;
	bool r;
	bool s;
} t_flags;

typedef struct s_buffer {
	const char *buffer;
	const char *filename;
	struct s_buffer *next;
	bool from_stdin;
} t_buffer;

typedef struct s_md5_ctx {
	uint32_t A, B, C, D;
	uint64_t count;
	uint8_t buffer[64];
} t_md5_ctx;

typedef struct s_sha256_ctx {
	uint32_t state[8];
	uint64_t count;
	uint8_t buffer[64];
} t_sha256_ctx;

//* Our beloved libft functions *//
int ft_strcmp(const char *s1, const char *s2);
size_t ft_strlen(const char *s);
void ft_memset(void *b, int c, size_t len);
void ft_memcpy(void *dst, const void *src, size_t len);
char *ft_strchr(const char *str, char c);
char *ft_strndup(const char *s, size_t n);

//* Main *//
void usage(const char **argv);
void md5(int argc, const char **argv);
void sha256(int argc, const char **argv);

//* Common utils */
void encode(uint8_t *output, uint32_t *input, size_t len);
void decode(uint32_t *output, const uint8_t *input, size_t len);

//* MD5 *//
void md5str(const t_buffer *buffer, t_flags flags);
void md5file(const t_buffer *file_buffer, t_flags flags);

//* SHA256 *//
void sha256str(const t_buffer *buffer, t_flags flags);
void sha256file(const t_buffer *file_buffer, t_flags flags);

#endif
