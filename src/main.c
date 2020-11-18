/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:19:47 by darodrig          #+#    #+#             */
/*   Updated: 2020/11/18 12:40:00 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static char
	*read_stdin(void)
{
	int		rd;
	char	buff[2];
	char	*str;

	str = ft_strdup("");
	buff[1] = 0;
	while ((rd = read(0, buff, 1)) > 0)
	{
		str = ft_append(str, *buff);
	}
	return (str);
}

static void
	usage(void)
{
	ft_puts("usage: ft_ssl command [command opts] [command args]");
	ft_puts("");
}

static void
	invalid_command(const char *s)
{
	ft_putstr("ft_ssl: Error: '");
	ft_putstr(s);
	ft_puts("' is an invalid command.");
	ft_puts("Standard commands:\n");
	ft_puts("Message Digest commands:");
	ft_puts("md5\nsha256\n");
	ft_puts("Cypher commands:");
	ft_puts("");
}

int
	main(int argc, char **argv)
{
	char *input;

	(void)input;
	(void)argc;
	(void)argv;

	ft_md5("hola");
	ft_md5("");
	ft_md5("asdfasdfasdfasdfa");
	exit(0);
	if (argc == 1)
		usage();
	if (argc == 2)
	{
		if (!ft_strcmp(argv[1], "md5"))
		{
			input = read_stdin();
			ft_puts(input);
			free(input);
		}
		else
			invalid_command(argv[1]);
	}
	/* print_bin(5);
	ft_puts("");
	print_bin(5 << 1);
	ft_puts("");
	print_bin(5 << 2);
	ft_puts("");
	print_bin(3);
	ft_puts("");
	print_bin(4457483668);
	printf("len %zu\n", strbitlen("asdf234523452234")); */
}
