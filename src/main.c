#include "../inc/ft_ssl.h"

static int usage()
{
	ft_putstr("");
	return (-1);
}

int main(int argc, char **argv)
{
	if (argc < 2)
		exit(usage());
	while(*++argv)
		ft_putstr(*argv);
}