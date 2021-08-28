NAME= ft_ssl

SRC = src/main.c
OBJ = $(SRC:.c=.o)
INC = inc/ft_ssl.h
LIBFT = libft/libft.a

FLAGS= -Wall -Wextra -Werror -Wformat-security -g -fsanitize=address

LIB= -I libft/libft.a



$(NAME): $(OBJ) $(INC)
	gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

$(OBJ): $(SRC) $(LIBFT)
	gcc $(FLAGS) -c $(SRC) -o $(OBJ)

$(LIBFT):
	$(MAKE) -C libft
clean:
	rm -f $(OBJ)
	$(MAKE) clean -C libft
fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all

all: $(NAME)

x: $(NAME)
	./$(NAME)
m:	$(NAME)
	./$(NAME) md5

push: fclean
	git add libft $(SRC) $(INC) Makefile
	git commit -m "d-r-e"
	git push

norm:
	@norminette -v
	norminette $(SRC) $(INC)