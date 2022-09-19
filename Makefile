CC = gcc -Werror -Wextra -Wall -lpthread
NAME = philo

SRC = philo.c utilities.c 
OBJSRC = $(SRC)

all : $(NAME)

$(NAME): $(OBJSRC)
	$(CC) $(FLAGS) $(OBJSRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(NAME)

re: fclean all
