NAME= ft_ssl

SRC = src/main.c src/utils.c src/libft.c

INC = inc/ft_ssl.h


FLAGS= -Wall -Wextra -Werror


$(NAME): $(SRC) $(INC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

clean:

fclean: clean
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