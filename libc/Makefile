NAME = libc.a

all: $(NAME)

$(NAME):
	gcc -Wall -Werror -Wextra -c *.cpp
	ar rc $(NAME) *.o
	ranlib $(NAME)

fclean: clean
	rm -fr $(NAME)

clean:
	rm -fr *.o

re: fclean all
