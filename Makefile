CC = gcc -Werror -Wextra -Wall -lpthread -fsanitize=thread -g 
NAME = philo

SRC = philo.c utilities.c cycle_of_a_life.c
OBJSRC = $(SRC)

all : $(NAME)

$(NAME): $(OBJSRC)
	$(CC) $(FLAGS) $(OBJSRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(NAME)

re: fclean all
