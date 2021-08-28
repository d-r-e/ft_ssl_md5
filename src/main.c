#include "../inc/ft_ssl.h"

static int ft_append(char **buff, char c)
{
	char    *tmp;
	int     len;

	if (!*buff)
		*buff = ft_strdup("");
	len = ft_strlen(*buff);
	tmp = ft_calloc(1, (len + 2) * sizeof(char));
	if (!tmp)
		return (-1);
	ft_strncpy(tmp, *buff, len);
	tmp[len] = c;
	tmp[len + 1] = 0;
	free(*buff);
	*buff = tmp;
	return (0);
}

static int usage(void)
{
	ft_puts("ft_md5: usage: ./ft_md5 [-spr] file");
	return (-1);
}

static void init_options(int argc, char **argv)
{
	ft_bzero(&g_ssl, sizeof(g_ssl));
	if (argc > 1 && !ft_strcmp("md5", argv[1]))
		g_ssl.md5 = 1;
	else
		exit(usage());
	for (int i = 2; i < argc; ++i)
	{
		if (!ft_strcmp(argv[i], "-p"))
			g_ssl.p = 1;
		if (!ft_strcmp(argv[i], "-q"))
			g_ssl.q = 1;
		if (!ft_strcmp(argv[i], "-r"))
			g_ssl.r = 1;
		if (!ft_strcmp(argv[i], "-s"))
		{
			if (argc > i)
				g_ssl.input = ft_strdup(argv[i + 1]);
			else
				exit(usage());
			g_ssl.s = 1;
		}
	}
}

int main(int argc, char **argv)
{
	char    *str = NULL;
	char    c;

	init_options(argc, argv);
	(void)argv;
	(void)argc;
	if (argc < 2)
	{
		while (read(0, &c, 1))
		{
			if (ft_append(&str, c))
			{
				free(str);
				return (-1);
			}
		}
		ft_md5(str, NULL);
		free(str);
	}
	t_word w = init_word(0xca,0xbb,0x11, 0);
	print_word(w);
	w = init_word(0,0,0,0);
	print_word(w);
	w = init_word_int(42);
	print_word(w);
	// system("leaks ft_ssl");
	return(0);
}