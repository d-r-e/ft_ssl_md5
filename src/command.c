#include "ft_ssl.h"

static
t_buffer *create_buffer(const char *buffer_content, const char *filename, bool from_stdin) {
    t_buffer *new_buffer; ;

    if (!(new_buffer = malloc(sizeof(t_buffer)))) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_buffer->buffer = buffer_content;
    new_buffer->filename = filename;
    new_buffer->from_stdin = from_stdin;
    new_buffer->next = NULL;
    return new_buffer;
}

static void append_buffer(t_buffer **list, t_buffer *new_buffer) {
	if (*list == NULL) {
		*list = new_buffer;
	} else {
		t_buffer *current = *list;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = new_buffer;
	}
}

static int parse_flags(int argc, const char **argv, t_md5_flags *flags, t_buffer **string_buffers) {
	bool found_file = false;

	for (int i = 2; i < argc; i++) {
		if (!found_file) {
			if (ft_strcmp(argv[i], "-p") == 0) {
				flags->p = true;
			} else if (ft_strcmp(argv[i], "-q") == 0) {
				flags->q = true;
			} else if (ft_strcmp(argv[i], "-r") == 0) {
				flags->r = true;
			} else if (ft_strcmp(argv[i], "-s") == 0) {
				flags->s = true;
				if (i + 1 >= argc) {
					fprintf(stderr, "%s: %s: option requires an argument -- s\n", argv[0], argv[1]);
					return 0;
				}
				t_buffer *new_buffer = create_buffer(argv[i + 1], NULL, false);
				append_buffer(string_buffers, new_buffer);
				i++;
			} else {
				found_file = true;
				t_buffer *new_buffer = create_buffer(NULL, argv[i], false);
				append_buffer(string_buffers, new_buffer);
			}
		} else {
			t_buffer *new_buffer = create_buffer(NULL, argv[i], false);
			append_buffer(string_buffers, new_buffer);
		}
	}

    if (flags->p) { // if -p is set, we need to read from stdin
        t_buffer *new_buffer = create_buffer(NULL, NULL, true);
        new_buffer->next = *string_buffers;
        *string_buffers = new_buffer;
    }

    if (!flags->p && !flags->s && *string_buffers == NULL) { // stdin by default
        t_buffer *new_buffer = create_buffer(NULL, NULL, true);
        *string_buffers = new_buffer;
    }

    return 1;
}

static
void clear_list(t_buffer *list) {
    t_buffer *tmp;
    while (list) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

static
void append_to_buffer(t_buffer **head, const char *data, size_t len) {
    t_buffer *new_node = malloc(sizeof(t_buffer));
    if (new_node == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_node->buffer = ft_strndup(data, len);
    if (new_node->buffer == NULL) {
        perror("ft_strndup");
        exit(EXIT_FAILURE);
    }
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
    } else {
        t_buffer *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

static
void from_string(t_md5_flags flags, t_buffer string_buffer) {
    md5main(&string_buffer, flags);
}

static
void from_stdin(t_md5_flags flags) {
	char buffer[BUFFER_SIZE];
	ssize_t bytes;
	bool read_stdin = false;
	t_buffer *head = NULL;

	while ((bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
		append_to_buffer(&head, buffer, bytes);
	}
	if (!head) {
		append_to_buffer(&head, "", 0);
	}
	read_stdin = true;
	if (read_stdin && head) {
		head->from_stdin = true;
		from_string(flags, *head);
	}

	t_buffer *current = head;
	while (current != NULL) {
		t_buffer *next = current->next;
		free(current);
		current = next;
	}
}

static
void from_file(t_md5_flags flags, t_buffer file_buffer) {
    md5file(&file_buffer, flags);
}

void exec_command(int argc, const char **argv) {
    t_md5_flags flags = {false, false, false, false};
    t_buffer *string_buffers = NULL;
    t_buffer *ptr;

    if (!parse_flags(argc, argv, &flags, &string_buffers)) {
        clear_list(string_buffers);
        return;
    }
    ptr = string_buffers;
    while (ptr) {
        if (ptr->buffer)
            from_string(flags, *ptr);
        else if (ptr->filename) {
            from_file(flags, *ptr);
        } else {
            from_stdin(flags);
        }
        ptr = ptr->next;
    }
    clear_list(string_buffers);
}
