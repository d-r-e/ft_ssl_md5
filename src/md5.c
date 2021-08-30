#include "../inc/ft_ssl.h"

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

void init_md5_words(t_md5 *md5)
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
	uint64_t	flen;
	int			nblocks;
	char		appendix = 0x80;

	flen = ssl->len + 1;
	md5->msg = malloc(sizeof(char) * ssl->len);
	ft_bzero(md5->msg, sizeof(char) * ssl->len);
	md5->msg = ft_memcpy(md5->msg, ssl->str, ssl->len);
	ft_append(&md5->msg, appendix);
	while (flen % 64 != 56)
	{
		ft_append(&md5->msg, '\0');
		flen++;
	}
	printf("len: %lu, flen: %lu\n", ssl->len, flen);
	nblocks = flen / 64 + 1;
	md5->blocks = (t_block*)malloc(nblocks * sizeof(t_block));
	ft_bzero(md5->blocks, sizeof(t_block) * nblocks);
	ft_memcpy(md5->blocks, md5->msg, ssl->len);
	for (int i = 0; i < nblocks; i++)
	{
		//ft_bzero(&md5->blocks[i].str, 64);
		if (i == nblocks - 1)
		{
			int len = ssl->len < 56 ? ssl->len : 56;
			ft_memcpy(md5->blocks[i].str, md5->msg + 64*i, len);
			ft_memcpy(md5->blocks[i].str + 56, (void*)&flen, sizeof(flen));
		}
		// else
		// // 	ft_memcpy(md5->blocks[i].str, md5->msg + 64*i, 64);
		print_block(md5->blocks[i]);
		//print_block(md5->blocks[i]);
	}
	free(md5->msg);
}

int ft_md5(t_ssl ssl)
{
	t_md5 md5;

	init_md5_words(&md5);
	set_msg(&ssl, &md5);
	print_md5_hash(md5);
	return (0);
}
