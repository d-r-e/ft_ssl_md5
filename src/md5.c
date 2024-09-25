#include <ft_ssl.h>

static const uint8_t PADDING[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define FF(a, b, c, d, x, s, ac)                                               \
	{                                                                          \
		(a) += F((b), (c), (d)) + (x) + (uint32_t) (ac);                       \
		(a) = ROTATE_LEFT((a), (s));                                           \
		(a) += (b);                                                            \
	}

#define GG(a, b, c, d, x, s, ac)                                               \
	{                                                                          \
		(a) += G((b), (c), (d)) + (x) + (uint32_t) (ac);                       \
		(a) = ROTATE_LEFT((a), (s));                                           \
		(a) += (b);                                                            \
	}

#define HH(a, b, c, d, x, s, ac)                                               \
	{                                                                          \
		(a) += H((b), (c), (d)) + (x) + (uint32_t) (ac);                       \
		(a) = ROTATE_LEFT((a), (s));                                           \
		(a) += (b);                                                            \
	}

#define II(a, b, c, d, x, s, ac)                                               \
	{                                                                          \
		(a) += I((b), (c), (d)) + (x) + (uint32_t) (ac);                       \
		(a) = ROTATE_LEFT((a), (s));                                           \
		(a) += (b);                                                            \
	}

/***
 * https://rosettacode.org/wiki/MD5#C
 * https://en.wikipedia.org/wiki/MD5
 * https://tools.ietf.org/html/rfc1321
 */
static void md5_init(t_md5_ctx *state) {
	state->A = 0x67452301;
	state->B = 0xEFCDAB89;
	state->C = 0x98BADCFE;
	state->D = 0x10325476;
	state->count = 0;
	ft_memset(state->buffer, 0, 64);
}

static void md5_transform(uint32_t *state, const uint8_t block[64]) {
	uint32_t a = state[0], b = state[1], c = state[2], d = state[3];
	uint32_t x[16];

	decode(x, block, 64);

	FF(a, b, c, d, x[0], 7, 0xd76aa478);
	FF(d, a, b, c, x[1], 12, 0xe8c7b756);
	FF(c, d, a, b, x[2], 17, 0x242070db);
	FF(b, c, d, a, x[3], 22, 0xc1bdceee);
	FF(a, b, c, d, x[4], 7, 0xf57c0faf);
	FF(d, a, b, c, x[5], 12, 0x4787c62a);
	FF(c, d, a, b, x[6], 17, 0xa8304613);
	FF(b, c, d, a, x[7], 22, 0xfd469501);
	FF(a, b, c, d, x[8], 7, 0x698098d8);
	FF(d, a, b, c, x[9], 12, 0x8b44f7af);
	FF(c, d, a, b, x[10], 17, 0xffff5bb1);
	FF(b, c, d, a, x[11], 22, 0x895cd7be);
	FF(a, b, c, d, x[12], 7, 0x6b901122);
	FF(d, a, b, c, x[13], 12, 0xfd987193);
	FF(c, d, a, b, x[14], 17, 0xa679438e);
	FF(b, c, d, a, x[15], 22, 0x49b40821);

	GG(a, b, c, d, x[1], 5, 0xf61e2562);
	GG(d, a, b, c, x[6], 9, 0xc040b340);
	GG(c, d, a, b, x[11], 14, 0x265e5a51);
	GG(b, c, d, a, x[0], 20, 0xe9b6c7aa);
	GG(a, b, c, d, x[5], 5, 0xd62f105d);
	GG(d, a, b, c, x[10], 9, 0x02441453);
	GG(c, d, a, b, x[15], 14, 0xd8a1e681);
	GG(b, c, d, a, x[4], 20, 0xe7d3fbc8);
	GG(a, b, c, d, x[9], 5, 0x21e1cde6);
	GG(d, a, b, c, x[14], 9, 0xc33707d6);
	GG(c, d, a, b, x[3], 14, 0xf4d50d87);
	GG(b, c, d, a, x[8], 20, 0x455a14ed);
	GG(a, b, c, d, x[13], 5, 0xa9e3e905);
	GG(d, a, b, c, x[2], 9, 0xfcefa3f8);
	GG(c, d, a, b, x[7], 14, 0x676f02d9);
	GG(b, c, d, a, x[12], 20, 0x8d2a4c8a);

	HH(a, b, c, d, x[5], 4, 0xfffa3942);
	HH(d, a, b, c, x[8], 11, 0x8771f681);
	HH(c, d, a, b, x[11], 16, 0x6d9d6122);
	HH(b, c, d, a, x[14], 23, 0xfde5380c);
	HH(a, b, c, d, x[1], 4, 0xa4beea44);
	HH(d, a, b, c, x[4], 11, 0x4bdecfa9);
	HH(c, d, a, b, x[7], 16, 0xf6bb4b60);
	HH(b, c, d, a, x[10], 23, 0xbebfbc70);
	HH(a, b, c, d, x[13], 4, 0x289b7ec6);
	HH(d, a, b, c, x[0], 11, 0xeaa127fa);
	HH(c, d, a, b, x[3], 16, 0xd4ef3085);
	HH(b, c, d, a, x[6], 23, 0x04881d05);
	HH(a, b, c, d, x[9], 4, 0xd9d4d039);
	HH(d, a, b, c, x[12], 11, 0xe6db99e5);
	HH(c, d, a, b, x[15], 16, 0x1fa27cf8);
	HH(b, c, d, a, x[2], 23, 0xc4ac5665);

	II(a, b, c, d, x[0], 6, 0xf4292244);
	II(d, a, b, c, x[7], 10, 0x432aff97);
	II(c, d, a, b, x[14], 15, 0xab9423a7);
	II(b, c, d, a, x[5], 21, 0xfc93a039);
	II(a, b, c, d, x[12], 6, 0x655b59c3);
	II(d, a, b, c, x[3], 10, 0x8f0ccc92);
	II(c, d, a, b, x[10], 15, 0xffeff47d);
	II(b, c, d, a, x[1], 21, 0x85845dd1);
	II(a, b, c, d, x[8], 6, 0x6fa87e4f);
	II(d, a, b, c, x[15], 10, 0xfe2ce6e0);
	II(c, d, a, b, x[6], 15, 0xa3014314);
	II(b, c, d, a, x[13], 21, 0x4e0811a1);
	II(a, b, c, d, x[4], 6, 0xf7537e82);
	II(d, a, b, c, x[11], 10, 0xbd3af235);
	II(c, d, a, b, x[2], 15, 0x2ad7d2bb);
	II(b, c, d, a, x[9], 21, 0xeb86d391);

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;

	ft_memset(x, 0, sizeof(x));
}

static void md5_update(t_md5_ctx *context, const uint8_t *input, size_t len) {
	size_t i;
	size_t j;
	size_t index;

	index = (context->count >> 3) & 63;
	context->count += ((uint64_t) len << 3);
	j = 64 - index;
	if (len >= j) {
		ft_memcpy(&context->buffer[index], input, j);
		md5_transform(&context->A, context->buffer);
		for (i = j; i + 63 < len; i += 64)
			md5_transform(&context->A, &input[i]);
		index = 0;
	} else {
		i = 0;
	}
	ft_memcpy(&context->buffer[index], &input[i], len - i);
}

static void md5_final(uint8_t digest[16], t_md5_ctx *context) {
	uint8_t bits[8];
	size_t index, pad_len;

	encode(bits, (uint32_t *) &context->count, 8);
	index = (context->count >> 3) % 64;
	pad_len = (index < 56) ? (56 - index) : (120 - index);
	md5_update(context, PADDING, pad_len);
	md5_update(context, bits, 8);
	encode(digest, &context->A, 4);
	encode(digest + 4, &context->B, 4);
	encode(digest + 8, &context->C, 4);
	encode(digest + 12, &context->D, 4);
	ft_memset(context, 0, sizeof(*context));
}

void print_digest(const t_buffer *buffer,
                  uint8_t digest[16],
                  t_flags flags,
                  uint8_t len,
                  const char *algorithm) {
	char *format = "%02x";
	char output[128];
	int pos = 0;

	if (flags.p && buffer && buffer->from_stdin &&
	    ft_strlen(ft_strchr(buffer->buffer, '\n')) == 1)
		*ft_strchr(buffer->buffer, '\n') = 0;
	for (int i = 0; i < len; i++)
		pos += sprintf(output + pos, format, digest[i]);
	if (flags.q) {
		if (flags.p && buffer && buffer->from_stdin)
			printf("%s\n", buffer->buffer);
		printf("%s\n", output);
	} else if (!flags.r) {
		if (buffer && buffer->filename)
			printf("%s (%s) = %s\n", algorithm, buffer->filename, output);
		else if (flags.p && buffer && buffer->buffer && buffer->from_stdin)
			printf("(\"%s\")= %s\n", buffer->buffer, output);
		else if (!flags.p && buffer && buffer->buffer && buffer->from_stdin)
			printf("(stdin)= %s\n", output);
		else if (buffer && buffer->buffer)
			printf("%s (\"%s\") = %s\n", algorithm, buffer->buffer, output);
	} else {
		if (buffer && buffer->filename)
			printf("%s %s\n", output, buffer->filename);
		else if (buffer && !buffer->from_stdin && buffer->buffer)
			printf("%s \"%s\"\n", output, buffer->buffer);
		else if (buffer && buffer->buffer)
			printf("(\"%s\")= %s\n", buffer->buffer, output);
	}
}

void md5str(const t_buffer *buffer, t_flags flags) {
	t_md5_ctx state;
	uint8_t digest[16];

	md5_init(&state);
	t_buffer *tmp = (t_buffer *) buffer;
	while (buffer) {
		md5_update(&state,
		           (const uint8_t *) buffer->buffer,
		           ft_strlen(buffer->buffer));
		buffer = buffer->next;
	}
	md5_final(digest, &state);
	print_digest(tmp, digest, flags, 16, "MD5");
}

void md5file(const t_buffer *file_buffer, t_flags flags) {
	int fd;
	ssize_t bytes_read;
	uint8_t buffer[BUFFER_SIZE];
	t_md5_ctx state;
	uint8_t digest[16];

	if ((fd = open(file_buffer->filename, O_RDONLY)) < 0) {
		printf("ft_ssl: md5: %s: %s\n", file_buffer->filename, strerror(errno));
		return;
	}
	md5_init(&state);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
		md5_update(&state, buffer, bytes_read);
	}
	close(fd);
	if (bytes_read == -1) {
        close(fd);
		printf("ft_ssl: md5: %s: %s\n", file_buffer->filename, strerror(errno));
		return;
	}
	md5_final(digest, &state);
	print_digest(file_buffer, digest, flags, 16, "MD5");
}