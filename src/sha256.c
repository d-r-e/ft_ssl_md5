#include <ft_ssl.h>



static
void sha256init(t_sha256_ctx *state) {
	(void) state;

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
}

void sha256file(const t_buffer *file_buffer, t_flags flags) {
	t_sha256_ctx state;
	//	uint8_t digest[32];

	sha256init(&state);

	(void) flags;
	(void) file_buffer;
}

void sha256str(const t_buffer *buffer, t_flags flags) {
	t_sha256_ctx state;
	//	uint8_t digest[32];

	sha256init(&state);

	(void) flags;
	(void) buffer;
}
