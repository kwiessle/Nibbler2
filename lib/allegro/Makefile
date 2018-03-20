NAME = allegro.so
COMPILATOR = g++
INC	= -I .. -I . -I ../Entity -I ~/.brew/include
SFML = -L ~/.brew/lib  -lallegro -lallegro_image -lallegro_main

SRC = WindowAllegro.cpp \
	../Entity/Entity.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "✏️ \033[33;5m[ALLEGRO] Creating extern lib\033[0m"
	@$(COMPILATOR) -fPIC $(OBJ) -shared $(SFML) -o $(NAME)


%.o: %.cpp
	@$(COMPILATOR) $(INC) -o $@ -c $< $(FLAGS)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : re fclean clean all
