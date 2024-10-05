NAME = ft_ssl
SRC = src/main.c src/help.c src/command.c src/libft.c src/md5.c src/sha256.c src/encoding.c
INCLUDE = ./inc/ft_ssl.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2
INC = -I./inc
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJ)

all: $(NAME)




%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

leaks: all
	./test/test.sh --valgrind

test: all
	./test/test.sh
.PHONY: clean fclean re all


