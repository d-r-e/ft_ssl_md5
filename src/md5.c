#include "../inc/ft_ssl.h"

static uint32_t k[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};

uint32_t s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
				5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
				4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
				6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

// static t_word f_function(t_word b, t_word c, t_word d)
// {
// 	t_word f;

// 	f.i = ( b.i & c.i ) | ( (!b.i) & d.i );
// 	ft_puts("a");
// 	return (f);
// }

// static t_word g_function(t_word b, t_word c, t_word d)
// {
// 	t_word f;

// 	f.i = ( b.i & d.i ) | ( c.i & (!d.i) );
// 		ft_puts("b");
// 	return (f);
// }

// static t_word h_function(t_word b, t_word c, t_word d)
// {
// 	t_word f;

// ft_puts("c");
// 	f.i = ( b.i ^ c.i ^ d.i );
// 	return (f);
// }

// static t_word i_function(t_word b, t_word c, t_word d)
// {
// 	t_word f;

// ft_puts("d");
// 	f.i = b.i ^ ( c.i | (!d.i) );
// 	return (f);
// }

static uint32_t shift(uint32_t x, uint32_t s)
{
	return (((x) << (s)) | ((x) >> (32 - (s))));
}

void put_md5(const char *file, const char *hash)
{
	if (file)
	{
		ft_putstr("MD5(");
		ft_putstr(file);
		ft_putstr(")= ");
	}
	ft_puts(hash);
}

void init_words(t_md5 *md5)
{
	ft_bzero(md5, sizeof(*md5));
	//md5->blocks = NULL;
	md5->a = init_word(0x01, 0x23, 0x45, 0x67);
	md5->b = init_word(0x89, 0xab, 0xcd, 0xef);
	md5->c = init_word(0xfe, 0xdc, 0xba, 0x98);
	md5->d = init_word(0x76, 0x54, 0x32, 0x10);
}

static void set_msg(t_ssl *ssl, t_md5 *md5)
{
	uint64_t flen;

	flen = (((((ssl->len + 8) / 64) + 1) * 64) - 8);
	md5->msg = ft_calloc(1, flen + 8);
	
	ft_memcpy(md5->msg, ssl->str, ssl->len);
	md5->msg[ssl->len] = 0x80;
	
	// if (flen != fflen)
	// 	printf("maaal\n");
	md5->nblocks = (flen / 64) + 1;
	md5->blocks = (t_block*)malloc(md5->nblocks * (sizeof (t_block)));
	//printf("len: %llu, flen: %llu, md5->nblocks: %d, fflen: %llu\n", ssl->len, flen, md5->nblocks, flen);
	uint32_t len_in_bits = ssl->len * 8;
	(void)len_in_bits;
	ft_bzero(md5->msg + flen, sizeof(len_in_bits * 2));
	ft_memcpy(md5->msg + flen, &len_in_bits, sizeof(len_in_bits));
	ft_bzero(md5->blocks, sizeof(t_block) * md5->nblocks);
	for (uint32_t i = 0; i < md5->nblocks; i++)
	{
		ft_bzero(md5->blocks[i].str, 64);
		ft_memcpy(md5->blocks[i].str, md5->msg + (64 * i), 64);
		// else
		// {
		//  	ft_memcpy(md5->blocks[i].str, &md5->msg[64 * i], 64);
		// }
		// for (int i = 0; i < 64; i++)
		// 	printf("%.2x", md5->blocks[i].str[i]);
		// ft_puts("");
		//print_block(md5->blocks[i]);
		//print_block(md5->blocks[i]);
	}
	md5->flen = flen;
}

void md5_loop(t_md5 *md5)
{
	uint32_t *word;
	uint32_t a, b, c, d = 0;
	uint32_t f, g;
	uint32_t i, temp;


	for (uint64_t offset = 0; offset < md5->flen; offset += 64)
	{
		word = (uint32_t *)(md5->msg + offset);

		//printf("offset: %lld %llx\n", offset, offset);
		a = md5->a.i;
		b = md5->b.i;
		c = md5->c.i;
		d = md5->d.i;
		for(i = 0; i < 64; i++)
		{
			if (i < 16)
            {
                f = (b & c) | ((~b) & (d));
                g = i;
            }
            else if (i < 32)
            {
                f = (d & b) | ((~d) & (c));
                g = ((5 * i) + 1) % 16;
            }
            else if (i < 48)
            {
                f = b ^ c ^ d;
                g = ((3 * i) + 5) % 16;
            }
            else
            {
                f = c ^ (b | (~d));
                g = (7 * i) % 16;
            }
			// printf("i: %u\n", i);
			// printf("f=%x g=%d w[g]=%x\n", f, g, word[g]);
			// printf("");
			temp = d;
			d = c;
			c = b;
			//printf("rotateLeft(%x + %x + %x + %x, %d)\n", a, f, k[i], word[g], s[i]);
			b = b + shift((a + f + k[i] + word[g]), s[i]);
			a = temp;
			
		}
		//ft_puts("");
		md5->a.i += a;
		md5->b.i += b;
		md5->c.i += c;
		md5->d.i += d;
		// print_md5_hash(*md5);
		// printf("offset: %llu\n", offset);
	}
	free(md5->msg);
}

int ft_md5(t_ssl ssl)
{
	t_md5 md5;

	ft_bzero(&md5, sizeof(md5));

	init_words(&md5);
	set_msg(&ssl, &md5);
	md5_loop(&md5);
	print_md5_hash(md5);
	return (0);
}
