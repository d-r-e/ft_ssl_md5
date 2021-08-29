NAME= ft_ssl

SRC = src/main.c src/md5.c src/byte.c
OBJ = $(SRC:.c=.o)
FLAGS= -O2 -Wall -Wextra -Werror -Wformat-security
LIBFT=libft/libft.a
INC=inc/$(NAME).h

$(NAME): $(LIBFT) $(OBJ) 
	gcc $(FLAGS) $(OBJ) -I libft -L libft -lft -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c $(INC)
	gcc $(FLAGS) -c -o $@ $<

clean:
	$(MAKE) clean -C libft
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all

all: $(NAME)

x: $(NAME)
	./$(NAME)
m:	$(NAME)
	echo 42 | ./$(NAME) md5

push: fclean
	git add libft $(SRC) $(INC) Makefile
	git commit -m "d-r-e"
	git push origin main

norm:
	@norminette -v
	norminette $(SRC) $(INC)