#include <ft_ssl.h>

static int execute_command(int argc, const char **argv) {
	t_command commands[] = {{"md5", exec_command},
	                        {"sha256", (void (*)(int, const char **)) NULL},
	                        {NULL, NULL}};

	for (int i = 0; commands[i].name; i++) {
		if (ft_strcmp(argv[1], commands[i].name) == 0 && commands[i].func) {
			commands[i].func(argc, argv);
			return 0;
		}
	}
	usage(argv);
	return -1;
}

int main(int argc, const char **argv) {
	if (argc < 2) {
		usage(argv);
		exit(EXIT_FAILURE);
	}
	return execute_command(argc, argv);
}