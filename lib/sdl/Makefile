NAME =sdl.so
COMPILATOR = g++
INC	= -I .. -I . -I ../Entity -I ~/.brew/include
FLAGS = -shared -fPIC

SCRIPT = install.sh

#SDL = -L /usr/local/Cellar/sdl2/ -lSDL2
SDL = -L ~/.brew/lib/ -lSDL2

SRC = Window.cpp \
	../Entity/Entity.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILATOR) $(FLAGS) $(OBJ) $(SDL) $(IMG) $(TTF) $(MXR) -o $(NAME)

%.o: %.cpp
	$(COMPILATOR) $(INC) -o $@ -c $< $(FLAGS)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)


re: fclean all

.PHONY : re fclean clean all
