NAME = ../../sdl.so
COMPILATOR = g++
FLAGS = -Werror -Wall -Wextra -std=c++11
INC	= -I . -I ../../include -I ~/.brew/include
SDL = -fPIC  -shared
SDL += -L ~/.brew/lib/ -lSDL2 -lSDL2_TTF

SRC = Window.cpp \
	../../Entity/Entity.cpp \
	../../Exception/Exception.cpp \


OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "✏️ \033[33;1m[SDL]\033[0m  dylib compiled\033[0m"
	@$(COMPILATOR) $(SDL) $(OBJ) -o $(NAME)

%.o: %.cpp
	@$(COMPILATOR) $(INC) -o $@ -c $< $(FLAGS)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : re fclean clean all
