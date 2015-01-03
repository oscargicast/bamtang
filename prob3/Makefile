NAME = main
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/lib
CC = g++

$(NAME) : $(OBJ)
	$(CC) $(SRC) $(CFLAGS) -o $(NAME)

all : $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

r : re
	rm -f *~
	rm -f *.o