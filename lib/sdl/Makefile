NAME = sdl.so
COMPILATOR = g++
FLAGS = -Werror -Wall -Wextra -std=c++11
INC	= -I .. -I . -I ../Entity -I ~/.brew/include
SDL = -fPIC  -shared
SDL += -L ~/.brew/lib/ -lSDL2 -lSDL2_TTF

SRC = Window.cpp \
	../Entity/Entity.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "✏️ \033[33;5m[SDL]  Creating extern lib\033[0m"
	@$(COMPILATOR) $(SDL) $(OBJ) -o $(NAME)

%.o: %.cpp
	@$(COMPILATOR) $(INC) -o $@ -c $< $(FLAGS)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : re fclean clean all
