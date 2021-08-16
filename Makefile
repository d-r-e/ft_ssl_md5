NAME= ft_ssl

SRC = src/main.c src/utils.c src/libft.c src/libft2.c src/md5.c src/bits.c
OBJ = $(SRC:.c=.o)
LIBFT=libft/libft.a
INC=inc/$(NAME).h


FLAGS= -O2 -Wall -Wextra -Werror -Wformat-security

$(NAME): $(OBJ) $(LIBFT) 
	gcc $(FLAGS) $(OBJ) -I libft -L libft -lft -lm -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c $(INC)
	gcc $(FLAGS) -c -o $@ $<

clean:
	$(MAKE) clean -C libft
	rm -f $(OBJ)
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