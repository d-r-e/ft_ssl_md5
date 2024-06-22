NAME=ft_ssl
SRC = ./src/main.c 

CC=gcc
CFLAGS=-Wall -g -O2 -Wextra -Werror -Wformat-security

INC=-I./inc

all: $(NAME)

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: clean re all make fclean