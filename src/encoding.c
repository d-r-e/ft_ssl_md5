#include <ft_ssl.h>


void encode(uint8_t *output, uint32_t *input, size_t len) {
	size_t i, j;
	for (i = 0, j = 0; j < len; i++, j += 4) {
		output[j] = (uint8_t) (input[i] & 0xff);
		output[j + 1] = (uint8_t) ((input[i] >> 8) & 0xff);
		output[j + 2] = (uint8_t) ((input[i] >> 16) & 0xff);
		output[j + 3] = (uint8_t) ((input[i] >> 24) & 0xff);
	}
}

void decode(uint32_t *output, const uint8_t *input, size_t len) {
	size_t i, j;
	for (i = 0, j = 0; j < len; i++, j += 4) {
		output[i] = ((uint32_t) input[j]) | (((uint32_t) input[j + 1]) << 8) |
					(((uint32_t) input[j + 2]) << 16) | (((uint32_t) input[j + 3]) << 24);
	}
}




