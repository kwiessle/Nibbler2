NAME = glfw.so
COMPILATOR = g++
FLAGS = -Werror -Wall -Wextra -std=c++11
INC	=  -I . -I ../../include -Iglfw/include  -I ~/.brew/include
GLFW = -fPIC -shared
GLFW += -framework GLUT -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
GLFW += -force_load ./glfw/src/libglfw3.a

SRC = WindowGlfw.cpp \
	../../Entity/Entity.cpp \
	../../GException/GException.cpp \

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "✏️ \033[33;5m[OPENGL] Creating extern lib\033[0m"
	@$(COMPILATOR) $(GLFW) $(OBJ) -o $(NAME)

%.o: %.cpp
	@$(COMPILATOR) $(INC) -o $@ -c $< $(FLAGS)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : re fclean clean all
