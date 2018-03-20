NAME = sdl.so
COMPILATOR = g++
INC	= -I .. -I . -I ../Entity -I ~/.brew/include

SDL = -L ~/.brew/lib/ -lSDL2 -lSDL2_TTF

SRC = Window.cpp \
	../Entity/Entity.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)


$(NAME): $(OBJ)
	@echo "✏️ \033[33;5m[SDL]  Creating extern lib\033[0m"
	@$(COMPILATOR) -fPIC $(OBJ) -shared $(SDL) -o $(NAME)



%.o: %.cpp
	@$(COMPILATOR) $(INC) -o $@ -c $< $(FLAGS)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : re fclean clean all
