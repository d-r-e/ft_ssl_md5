NAME = ft_ssl
SRC = ./src/main.c ./src/help.c
INCLUDE = ./inc/ft_ssl.h
CC = gcc
CFLAGS = -Wall -g -O2 -Wextra -Werror -Wformat-security
INC = -I./inc

ifeq ($(shell uname), Linux)
    NPROC := $(shell nproc)
else ifeq ($(shell uname), Darwin)
    NPROC := $(shell sysctl -n hw.ncpu)
else
    NPROC := 1
endif

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

.PHONY: clean fclean re all

MAKEFLAGS += -j$(NPROC)
