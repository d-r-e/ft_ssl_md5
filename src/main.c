#include "../inc/ft_ssl.h"

int ft_append(char **buff, char c)
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

int main(int argc, char **argv)
{
	char    *str;
	char    c;

	if (argc == 2)
		ft_puts(argv[1]);
	while (read(0, &c, 1))
	{
		if (ft_append(&str, c))
		{
			free(str);
			return (-1);
		}
	}
	ft_md5(str);
	ft_putstr(str);
	free(str);
	// system("leaks ft_ssl");
	return(0);
}