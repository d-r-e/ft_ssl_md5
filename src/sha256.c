#include <ft_ssl.h>

# define ROTATE_RIGHT(x, n) (((x) >> (n)) | ((x) << (32-(n))))
#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTATE_RIGHT(x, 2) ^ ROTATE_RIGHT(x, 13) ^ ROTATE_RIGHT(x, 22))
#define EP1(x) (ROTATE_RIGHT(x, 6) ^ ROTATE_RIGHT(x, 11) ^ ROTATE_RIGHT(x, 25))
#define SIG0(x) (ROTATE_RIGHT(x, 7) ^ ROTATE_RIGHT(x, 18) ^ ((x) >> 3))
#define SIG1(x) (ROTATE_RIGHT(x, 17) ^ ROTATE_RIGHT(x, 19) ^ ((x) >> 10))

#define SHA256_BLOCK_SIZE 64

static const uint32_t k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

/**
 * https://www.openssl.org/docs/manmaster/man3/SHA256_Init.html
 */
static
void sha256init(t_sha256_ctx *state) {
	ft_memset(state->buffer, 0, 64);
	state->state[0] = 0x6a09e667;
	state->state[1] = 0xbb67ae85;
	state->state[2] = 0x3c6ef372;
	state->state[3] = 0xa54ff53a;
	state->state[4] = 0x510e527f;
	state->state[5] = 0x9b05688c;
	state->state[6] = 0x1f83d9ab;
	state->state[7] = 0x5be0cd19;
	state->count = 0;
	(void)k;
}

static void sha256_transform(t_sha256_ctx *ctx, const uint8_t data[]) {
	uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
	for (; i < 64; ++i)
		m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

	a = ctx->state[0];
	b = ctx->state[1];
	c = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];
	f = ctx->state[5];
	g = ctx->state[6];
	h = ctx->state[7];

	for (i = 0; i < 64; ++i) {
		t1 = h + EP1(e) + CH(e, f, g) + k[i] + m[i];
		t2 = EP0(a) + MAJ(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}

	ctx->state[0] += a;
	ctx->state[1] += b;
	ctx->state[2] += c;
	ctx->state[3] += d;
	ctx->state[4] += e;
	ctx->state[5] += f;
	ctx->state[6] += g;
	ctx->state[7] += h;
}

static void sha256_update(t_sha256_ctx *state, const uint8_t *data, size_t len) {
	size_t i, j;

	j = (state->count >> 3) & 63;
	state->count += len << 3;
	if ((j + len) > 63) {
		ft_memcpy(&state->buffer[j], data, (i = 64 - j));
		sha256_transform(state, state->buffer);
		for (; i + 63 < len; i += 64) {
			sha256_transform(state, &data[i]);
		}
		j = 0;
	} else {
		i = 0;
	}
	ft_memcpy(&state->buffer[j], &data[i], len - i);
}


static void sha256final(uint8_t *digest, t_sha256_ctx *state) {
	uint8_t finalcount[8];
	uint32_t i;

	for (i = 0; i < 8; i++)
		finalcount[i] = (uint8_t)((state->count >> ((7 - i) * 8)) & 255);
	sha256_update(state, (uint8_t *)"\200", 1);
	while ((state->count & 504) != 448)
		sha256_update(state, (uint8_t *)"\0", 1);
	sha256_update(state, finalcount, 8);

	for (i = 0; i < 32; i++)
		digest[i] = (uint8_t)((state->state[i >> 2] >> ((3 - (i & 3)) * 8)) & 255);
}

void sha256file(const t_buffer *file_buffer, t_flags flags) {
	int fd;
	ssize_t bytes_read;
	t_sha256_ctx state;
	uint8_t digest[32];

	sha256init(&state);
	fd = open(file_buffer->buffer, O_RDONLY);
	if (fd < 0) {
		dprintf(2, "ft_ssl: sha256: %s: %s\n", file_buffer->buffer, strerror(errno));
		return;
	}
	while ((bytes_read = read(fd, state.buffer, 64)) > 0) {
		sha256_update(&state, state.buffer, bytes_read);
	}
	sha256final(digest, &state);
	print_digest(file_buffer, digest, flags, 16);
}

void print_initial_digest(t_sha256_ctx *state) {
	for (int i = 0; i < 8; i++) {
		printf("%08x", state->state[i]);
	}
	printf("\n");
}


void sha256str(const t_buffer *buffer, t_flags flags) {
	t_sha256_ctx state;
	uint8_t digest[32];
	sha256init(&state);

	t_buffer *ptr = (t_buffer *)buffer;
	while (ptr) {
		sha256_update(&state, (const uint8_t *)ptr->buffer, ft_strlen(ptr->buffer));
		ptr = ptr->next;
	}
	sha256final(digest, &state);
	print_digest(buffer, digest, flags, 32);
}