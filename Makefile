NAME = cub
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c file_reading.c  textures_colors.c utilis.c parsing_element.c map.c
	  
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
test: $(NAME)
	chmod +x tex.sh
	./tex.sh

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
