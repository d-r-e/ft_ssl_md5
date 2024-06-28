#include <ft_ssl.h>

# define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
# define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
# define H(x, y, z) ((x) ^ (y) ^ (z))
# define I(x, y, z) ((y) ^ ((x) | (~z)))

# define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

# define FF(a, b, c, d, x, s, ac) { \
    (a) += F((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}

# define GG(a, b, c, d, x, s, ac) { \
    (a) += G((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}

# define HH(a, b, c, d, x, s, ac) { \
    (a) += H((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}

# define II(a, b, c, d, x, s, ac) { \
    (a) += I((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}


/***
 * https://rosettacode.org/wiki/MD5#C
 * https://en.wikipedia.org/wiki/MD5
 * https://tools.ietf.org/html/rfc1321
 */
static void md5_init(t_md5_ctx *state)
{
    state->A = 0x67452301;
    state->B = 0xEFCDAB89;
    state->C = 0x98BADCFE;
    state->D = 0x10325476;
    state->count = 0;
    ft_memset(state->buffer, 0, 64);
}

void encode(uint8_t *output, const uint32_t *input, size_t len)
{
    size_t i, j;

    for (i = 0, j = 0; j < len; i++, j += 4)
    {
        output[j] = (uint8_t)(input[i] & 0xFF);
        output[j + 1] = (uint8_t)((input[i] >> 8) & 0xFF);
        output[j + 2] = (uint8_t)((input[i] >> 16) & 0xFF);
        output[j + 3] = (uint8_t)((input[i] >> 24) & 0xFF);
    }
}




const char *state_to_string(t_md5_ctx *state)
{
    static char buffer[33];
    char c;
    memset(buffer, '\0', 33);
    encode((uint8_t *)buffer, (uint32_t *)&state->A, 4);
    encode((uint8_t *)&buffer[8], (uint32_t *)&state->B, 4);
    encode((uint8_t *)&buffer[16], (uint32_t *)&state->C, 4);
    encode((uint8_t *)&buffer[24], (uint32_t *)&state->D, 4);

    static char hex_output[65];
    for (int i = 0; i < 32; i++)
    {
        c = buffer[i / 2];
        if (i % 2 == 0)
            hex_output[i] = (c >> 4) & 0xF;
        else
            hex_output[i] = c & 0xF;
        hex_output[i] += (hex_output[i] < 10) ? '0' : 'a' - 10;
    }
    hex_output[64] = '\0';
    printf("%s\n", hex_output);
    return hex_output;
}



const char *md5main(const char *buffer)
{
    t_md5_ctx state;

    md5_init(&state);
    state_to_string(&state);
    return (buffer);
}
