NAME= ft_ssl

SRC = src/main.c

INC = inc/ft_ssl.h


FLAGS= -Wall -Wextra -Werror

libft:
	make -C ./src/libft

$(NAME): $(SRC) $(INC)
	make -C ./src/libft
	gcc $(FLAGS) $(SRC) -L. src/libft/libft.a -o $(NAME)

clean:
	make -C ./src/libft clean
	rm -f libft.a

fclean: clean
	make -C ./src/libft fclean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

x: re
	./$(NAME)

push: fclean
	git add $(SRC) $(INC) Makefile
	git commit -m "d-r-e"
	git push

norm:
	norminette $(SRC) $(INC)