#include "../inc/ft_ssl.h"

int ft_append(char **buff, char c)
{
	char    *tmp;
	int     len;

	if (*buff == NULL)
	{
		ft_puts("nobuff");
		*buff = ft_strdup("");
	}
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

int ft_append_at(char **buff, char c, unsigned int pos)
{
	char    *tmp;

	tmp = (char*)malloc((pos + 1));
	if (!tmp)
		return (-1);
	ft_memcpy(tmp, *buff, pos);
	tmp[pos] = c;
	free(*buff);
	*buff = tmp;
	return (0);
}

static int usage(void)
{
	ft_puts("ft_md5: usage: ./ft_md5 [md5/sha256] [-spr] [args]");
	return (-1);
}

static void init_options(int argc, char **argv)
{
	ft_bzero(&g_ssl, sizeof(g_ssl));
	if (argc > 1 && !ft_strcmp("md5", argv[1]))
		g_ssl.md5 = 1;
	else if (argc > 1 && !ft_strcmp("sha256", argv[1]))
		g_ssl.sha256 = 1;
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

static void print_algo(void)
{
	if (g_ssl.q)
		return;

	if (g_ssl.md5)
		printf("MD5(\"");
	else if (g_ssl.sha256)
		printf("SHA256(");
	printf("%s", g_ssl.str);
	printf("\") = ");
}

int main(int argc, char **argv)
{
	char    c;
	int		(*command[])() = { ft_md5 };
	uint64_t	len = 0;

	init_options(argc, argv);
	if (g_ssl.md5 && !g_ssl.s)
	{
		g_ssl.str = ft_strdup("");
		while (read(0, &c, 1))
		{
			len++;
			if (ft_append(&g_ssl.str, c))
			{
				free(g_ssl.str);
				return (-1);
			}
		}
		//printf("\"%s\"\n", g_ssl.str);
		g_ssl.len = len;
		print_algo();
		command[0](g_ssl);
		free(g_ssl.str);
	}
	else if (g_ssl.md5 && g_ssl.s)
	{
		g_ssl.str = g_ssl.input;
		g_ssl.len = ft_strlen(g_ssl.str);
		print_algo();
		command[0](g_ssl);
	}
	else if (g_ssl.md5 && !g_ssl.s)
	{
		;
	}
	else if (argc > 1)
		ft_putstr("error: invalid command\nStandard commands:\n\nMessage Digest Commands:\nmd5\nsha256\n");
	

	// system("leaks ft_ssl");
	return(0);
}