NAME= ft_ssl

SRC = src/main.c

INC = inc/ft_ssl.h


FLAGS= -Wall -Wextra -Werror

libft:
	make -C ./src/libft

$(NAME): $(SRC) $(INC) libft
	gcc $(FLAGS) $(SRC) -l ./src/libft/libft.a -o $(NAME)

clean:
	make -C ./src/libft clean

fclean: clean
	make -C ./src/libft fclean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

x: re
	./$(NAME)

push:
	git add $(SRC) $(INC) Makefile
	git commit -m "d-r-e"
	git push


