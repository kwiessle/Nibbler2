NAME = sfml.so
COMPILATOR = g++
INC	= -I .. -I . -I ../Entity -I ~/.brew/include
SFML = -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics

SRC = WindowSfml.cpp \
	../Entity/Entity.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "✏️ \033[33;5m[SFML] Creating extern lib\033[0m"
	@$(COMPILATOR) -fPIC $(OBJ) -shared $(SFML) -o $(NAME)


%.o: %.cpp
	@$(COMPILATOR) $(INC) -o $@ -c $< $(FLAGS)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : re fclean clean all
