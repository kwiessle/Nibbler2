NAME = sfml.so
COMPILATOR = g++
INC	= -I .. -I . -I ../Entity

SFML = -lsfml-graphics -lsfml-window -lsfml-system

SRC = Window.cpp \
	../Entity/Entity.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILATOR) -fPIC $(OBJ) -shared $(SFML) -o $(NAME)


%.o: %.cpp
	$(COMPILATOR) $(INC) -o $@ -c $< $(FLAGS)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : re fclean clean all
