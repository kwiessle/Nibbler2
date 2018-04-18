NAME = ../../sfml.so
COMPILATOR = clang++
FLAGS = -Werror -Wall -Wextra -std=c++11
INC	= -I . -I ../../include -I sfml/include
SFML = -fPIC -shared
SFML += -Lsfml/lib -lsfml-system -lsfml-window -lsfml-graphics

SRC = WindowSfml.cpp \
	../../Entity/Entity.cpp \
	../../Exception/Exception.cpp \

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "✏️ \033[33;1m[SFML]\033[0m dylib compiled\033[0m"
	@$(COMPILATOR) $(SFML) $(OBJ) -o $(NAME)

%.o: %.cpp
	@$(COMPILATOR) $(INC) -o $@ -c $< $(FLAGS)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : re fclean clean all
