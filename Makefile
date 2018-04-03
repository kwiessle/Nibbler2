NAME = Nibbler
LOGIN = kwiessle/vquesnel
COMPILATOR = g++ -g
INC	= -I . -I lib -I Game -I Player -I Timer
FLAGS = -Werror -Wall -Wextra -std=c++11
LDFLAGS = -rpath ./lib/sfml/sfml/lib
SRC = main.cpp \
			BinaryCall.cpp \
			Game/Game.cpp \
			Player/Player.cpp \
			Timer/Timer.cpp


OBJ = $(SRC:.cpp=.o)

GREEN = '\033[1;32m'
BLUE = '\033[1;36m'
RED = '\033[1;31m'

all: _assets _install sdl sfml glfw $(NAME)

$(NAME): $(OBJ)
	@$(COMPILATOR) $(LDFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[36;5m✅ Nibbler compiled"

%.o: %.cpp
	@$(COMPILATOR) $(FLAGS) $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ)
	@make clean -C ./lib/sdl
	@make clean -C ./lib/sfml
	@make clean -C ./lib/glfw
	@echo "\033[38;5;204m🗑 Object files removed"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C ./lib/sdl
	@make fclean -C ./lib/sfml
	@make fclean -C ./lib/glfw
	@echo "\033[38;5;204m🗑 Nibbler removed"

re: fclean all

lib: sdl sfml glfw

_install:
	./install.sh

_assets:
	@echo "📡 \033[36;5mDownloading archive...\033[0m"
	@mkdir -p assets
	@curl -o ./assets.zip -s https://transfer.sh/ZFcEp/assets.zip
	@unzip -q ./assets.zip  -d ./assets
	@rm -rf  __MACOSX/\*
	@rm ./assets.zip
	@echo "\033[38;5;82m✅ Assets downloaded"

aclean:
	@rm -rf assets schemes.pdf
	@echo "\033[38;5;204m🗑 Assets removed"

dsclean:
	@rm -rf .DS_S*
	@rm -rf */.DS_S*
	@echo "\033[38;5;204m🗑 All '.DS_STORE' files removed"

sdl:
	@make re -C ./lib/sdl
sfml:
	@make re -C ./lib/sfml
glfw:
	@make re -C ./lib/glfw
allegro:
	@make re -C ./lib/allegro

.PHONY : re fclean clean all libs aclean dsclean sdl sfml glfw
