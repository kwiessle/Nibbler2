NAME = Nibbler
LOGIN = kwiessle/vquesnel
COMPILATOR = clang++
INC	=  -I lib -I include
FLAGS = -Werror -Wall -Wextra -std=c++11
LDFLAGS = -rpath ./lib/sfml/sfml/lib
SRC = main.cpp \
	BinaryCall.cpp \
	Game/Game.cpp \
	Player/Player.cpp \
	Timer/Timer.cpp \
	Exception/Exception.cpp \
	Entity/Entity.cpp


OBJ = $(SRC:.cpp=.o)

GREEN = '\033[1;32m'
BLUE = '\033[1;36m'
RED = '\033[1;31m'

install: _install all

all: $(NAME) sdl sfml glfw audio

lib: sdl sfml glfw audio

game: $(NAME)

$(NAME): $(OBJ)
	@$(COMPILATOR) $(LDFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[36;1m✅ Nibbler compiled\033[0m"

%.o: %.cpp
	@$(COMPILATOR) $(FLAGS) $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ)
	@make clean -C ./lib/sdl
	@make clean -C ./lib/sfml
	@make clean -C ./lib/glfw
	@echo "\033[38;5;204m🗑 Object files removed\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C ./lib/sdl
	@make fclean -C ./lib/sfml
	@make fclean -C ./lib/glfw
	@echo "\033[38;5;204m🗑 Nibbler removed\033[0m"

re: fclean all

_install:
	@./install.sh

aclean:
	@rm -rf assets
	@echo "\033[38;5;204m🗑 Assets removed\033[0m"

dsclean:
	@rm -rf .DS_S*
	@rm -rf */.DS_S*
	@echo "\033[38;5;204m🗑 All '.DS_STORE' files removed\033[0m"

sdl:
	@make re -C ./lib/sdl

sfml:
	@make re -C ./lib/sfml

glfw:
	@make re -C ./lib/glfw

audio:
	@make re -C ./CoreAudio

.PHONY : re fclean clean all libs aclean dsclean sdl sfml glfw game install
