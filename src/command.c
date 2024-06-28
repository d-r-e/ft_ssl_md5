#include "ft_ssl.h"

static int parse_flags(int argc, const char **argv, t_md5_flags *flags, t_buffer **string_buffers)
{
    for (int i = 2; i < argc; i++)
    {
        if (ft_strcmp(argv[i], "-p") == 0)
        {
            flags->p = true;
            t_buffer *new_buffer = malloc(sizeof(t_buffer));
            if (!new_buffer)
            {
                perror("malloc");
                return 0;
            }
            new_buffer->filename = NULL;
            new_buffer->buffer = NULL;
            new_buffer->next = *string_buffers;
            *string_buffers = new_buffer;
        }
        else if (ft_strcmp(argv[i], "-q") == 0)
        {
            flags->q = true;
        }
        else if (ft_strcmp(argv[i], "-r") == 0)
        {
            flags->r = true;
        }
        else if (ft_strcmp(argv[i], "-s") == 0)
        {
            flags->s = true;
            if (i + 1 >= argc)
            {
                printf("%s: %s: option requires an argument -- s\n", argv[0], argv[1]);
                return 0;
            }
            t_buffer *new_buffer = malloc(sizeof(t_buffer));
            if (!new_buffer)
            {
                perror("malloc");
                return 0;
            }
            new_buffer->buffer = argv[i + 1];
            new_buffer->filename = NULL;
            new_buffer->next = *string_buffers;
            *string_buffers = new_buffer;
            i++;
        }
        else
        {
            if (argv[i][0] == '-')
            {
                printf("%s: %s: illegal option -- %c\n", argv[0], argv[1], argv[i][1]);
                return 0;
            }
            else
            {
                t_buffer *new_buffer = malloc(sizeof(t_buffer));
                if (!new_buffer)
                {
                    perror("malloc");
                    return 0;
                }
                new_buffer->filename = argv[i];
                new_buffer->buffer = NULL;
                new_buffer->next = *string_buffers;
                *string_buffers = new_buffer;
            }
        }
    }
    if (!flags->p && !flags->s && !*string_buffers)
    {
        t_buffer *new_buffer = malloc(sizeof(t_buffer));
        if (!new_buffer)
        {
            perror("malloc");
            return 0;
        }
        new_buffer->filename = NULL;
        new_buffer->buffer = NULL;
        new_buffer->next = *string_buffers;
        *string_buffers = new_buffer;
    }
    return 1;
}

static void clear_list(t_buffer *list)
{
    t_buffer *tmp;
    while (list)
    {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

void from_stdin(t_md5_flags flags)
{
    int fd = 0;
    char buffer[1024];
    ssize_t bytes_read;
    bool read_stdin = false;

    if (flags.p)
        write(1, "(\"", 2);
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
    {
        if (flags.p && !flags.q)
        {
            write(1, buffer, bytes_read);
        }
        read_stdin = true;
    }
    write(1, ")= ", 3);
    if (read_stdin && !flags.q && !flags.p)
    {
        printf("(stdin)= 35f1d6de0302e2086a4e472266efb3a9\n");
    }
}

void from_string(t_md5_flags flags, t_buffer string_buffer)
{

    (void)flags;
    (void)string_buffer;
    md5main(string_buffer.buffer);
}

void from_file(t_md5_flags flags, t_buffer file_buffer)
{

    (void)flags;
    (void)file_buffer;
    printf("3ba35f1ea0d170cb3b9a752e3360286c %s\n", file_buffer.filename);
}

void exec_command(int argc, const char **argv)
{
    t_md5_flags flags = {false, false, false, false};
    t_buffer *string_buffers = NULL;
    t_buffer *ptr;

    if (!parse_flags(argc, argv, &flags, &string_buffers))
    {
        clear_list(string_buffers);
        return;
    }
    ptr = string_buffers;
    // #ifdef DEBUG
    //     printf("Flag -p: %s, Flag -q: %s, Flag -r: %s\n",
    //            flags.p ? "true" : "false",
    //            flags.q ? "true" : "false",
    //            flags.r ? "true" : "false");
    // #endif
    while (ptr)
    {
        if (ptr->buffer)
        {
            from_string(flags, *ptr);
        }
        else if (ptr->filename)
        {
            from_file(flags, *ptr);
        }
        else
        {
            from_stdin(flags);
        }
        ptr = ptr->next;
    }
    clear_list(string_buffers);
}
