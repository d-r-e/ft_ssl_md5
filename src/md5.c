/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:32:35 by darodrig          #+#    #+#             */
/*   Updated: 2020/11/19 10:02:26 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

/*
** This is the main MD5 algorithm.
** input: string to convert
** output: 128 bit hash, null-terminated
*/

/* void md5_padding(char **msg)
{
	
} */

void	step12(t_md5	*m)
{
	void	*ptr;
	uint8_t *ptr2;
	int		i;

	m->len0 = strbitlen(m->msg);
	m->len1 =  8;
	while ((m->len0 + m->len1) % 512 != 448)
		m->len1 += 8;
	m->padded = malloc(sizeof(uint8_t) * (m->len1 / 8));
	ft_bzero(m->padded, sizeof(uint8_t) * (m->len1 / 8));
	
	ft_memcpy(m->padded, m->msg, m->len0 / 8);
	m->padded[m->len0 / 8] = 0b10000000;
	ptr = &m->padded[(int)((m->len0 + m->len1) / 8) - 8];
	ptr2 = ptr;
	i = 0;
	while ( i < 8)
	{
		*(ptr2 + (8 - i)) = (m->len0 % (int)powf(2, 64 * i));
		++i;
	}
	ft_puts("");
	ft_putnbr(m->len0);
	ft_puts("");
	write(1, "\n", 1);
	ft_puts(m->msg);
	printf("NUM%llu\n", m->len0);
	//free(m->msg);
	printbin(m->padded, (m->len0 + m->len1) / 8);
}

void step3(t_md5 *md5)
{
	md5->a = 0x67452301;
	md5->b = 0xEFCDAB89;
	md5->c = 0x98BADCFE;
	md5->d = 0x10325476;
}

char	*ft_md5(const char *input)
{
	t_md5 md5;

	ft_bzero(&md5, sizeof(t_md5));
	md5.msg = ft_strdup(input);
	step12(&md5);
	return (NULL);
}


void test_md5(const char *msg)
{
	t_md5	m;
	int		i;

	i = 0;
	m.msg = ft_strdup(msg);
	m.len0 = strbitlen(m.msg);
	m.len1 = m.len0 + 8;
	while ((m.len1) % 512 != 448)
		m.len1++;
	m.padded = malloc(sizeof(uint8_t) * m.len1);
	ft_bzero(m.padded, m.len1 / 8);
	ft_puts("");
	ft_memcpy(m.padded, m.msg, m.len0 / 8);
	m.padded[m.len0 / 8] = 128;
	printbin(m.padded, m.len1 / 8);
	
}