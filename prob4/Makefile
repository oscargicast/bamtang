NAME = main
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/lib
LINKER_FLAGS = -lGL -lGLU -lglut -lm -lGLEW -lSOIL
CC = g++

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(LIBDIR) $< $(LINKER_FLAGS) -o $@

all : $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

r : re
	rm -f *~
	rm -f *.o