#include "ft_ssl.h"

static int parse_flags(int argc, const char **argv, t_md5_flags *flags, t_buffer **string_buffers) {
    for (int i = 2; i < argc; i++) {
        if (ft_strcmp(argv[i], "-p") == 0) {
            flags->p = true;
        } else if (ft_strcmp(argv[i], "-q") == 0) {
            flags->q = true;
        } else if (ft_strcmp(argv[i], "-r") == 0) {
            flags->r = true;
        } else if (ft_strcmp(argv[i], "-s") == 0) {
            if (i + 1 >= argc) {
                printf("%s: %s: option requires an argument -- s\n", argv[0], argv[1]);
                return 0;
            }
            t_buffer *new_buffer = malloc(sizeof(t_buffer));
            new_buffer->buffer = argv[i + 1];
            new_buffer->next = *string_buffers;
            *string_buffers = new_buffer;
            i++;
        } else {
            if (argv[i][0] == '-') {
                printf("ft_ssl: md5: illegal option -- %s\n", argv[i] + 1);
            } else {
                t_buffer *new_buffer = malloc(sizeof(t_buffer));
                new_buffer->filename = argv[i];
                new_buffer->next = *string_buffers;
                *string_buffers = new_buffer;
                i++;

            }
        }
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


void md5(int argc, const char **argv) {
    t_md5_flags flags = {false, false, false};
    t_buffer *string_buffers = NULL;
    (void)parse_flags(argc, argv, &flags, &string_buffers);

#ifdef DEBUG
    t_buffer *ptr;
    printf("Flag -p: %s, Flag -q: %s, Flag -r: %s\n",
           flags.p ? "true" : "false",
           flags.q ? "true" : "false",
           flags.r ? "true" : "false");
    ptr = string_buffers;
    while (ptr) {
        if (ptr->buffer)
            printf("String: %s\n", ptr->buffer);
        else if (ptr->filename)
            printf("Filename: %s\n", ptr->filename);
        ptr = ptr->next;
    }
#endif


    clear_list(string_buffers);
}

