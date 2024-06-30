#include "ft_ssl.h"

static t_buffer *create_buffer(const char *buffer_content, const char *filename, bool from_stdin) {
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

static int parse_flags(int argc, const char **argv, t_md5_flags *flags, t_buffer **string_buffers) {
    for (int i = 2; i < argc; i++) {
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
            if (*string_buffers == NULL) {
                *string_buffers = new_buffer;
            } else {
                t_buffer *ptr = *string_buffers;
                while (ptr->next != NULL) {
                    ptr = ptr->next;
                }
                ptr->next = new_buffer;
            }
            i++;
        } else {
            if (argv[i][0] == '-') {
                printf("%s: %s: illegal option -- %c\n", argv[0], argv[1], argv[i][1]);
                return 0;
            } else {
                t_buffer *new_buffer = create_buffer(NULL, argv[i], false);
                new_buffer->next = *string_buffers;
                *string_buffers = new_buffer;
            }
        }
    }

    if (flags->p) {
        t_buffer *new_buffer = create_buffer(NULL, NULL, true);
        new_buffer->next = *string_buffers;
        *string_buffers = new_buffer;
    }

    if (!flags->p && !flags->s && *string_buffers == NULL) {
        t_buffer *new_buffer = create_buffer(NULL, NULL, true);
        *string_buffers = new_buffer;
    }

    return 1;
}

static void clear_list(t_buffer *list) {
    t_buffer *tmp;
    while (list) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

void append_to_buffer(t_buffer **head, const char *data, size_t len) {
    t_buffer *new_node = malloc(sizeof(t_buffer));
    if (new_node == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_node->buffer = ft_strndup(data, len);
    if (new_node->buffer == NULL) {
        perror("strndup");
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

void from_string(t_md5_flags flags, t_buffer string_buffer) {
    md5main(&string_buffer, flags);
}

void from_stdin(t_md5_flags flags) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;
    bool read_stdin = false;
    t_buffer *head = NULL;

    while ((bytes_read = getline(&buffer, &buffer_size, stdin)) > 0) {
        append_to_buffer(&head, buffer, bytes_read);
        read_stdin = true;
    }
    free(buffer);
    if (read_stdin && head) {
        head->from_stdin = true;
        from_string(flags, *head);
    }
}


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
        } else
            from_stdin(flags);
        ptr = ptr->next;
    }
    clear_list(string_buffers);
}
