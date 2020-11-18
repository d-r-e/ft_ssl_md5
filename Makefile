NAME= ft_ssl

SRC = src/main.c src/utils.c src/libft.c src/libft2.c src/md5.c src/bits.c

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
m:	re
	./$(NAME) md5

push: fclean
	git add $(SRC) $(INC) Makefile
	git commit -m "d-r-e"
	git push

norm:
	norminette $(SRC) $(INC)