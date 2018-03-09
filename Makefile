NAME = Nibbler
LOGIN = kwiessle/vquesnel
COMPILATOR = g++
INC	= -I . -I lib -I Game -I Player -I Timer
FLAGS = -Werror -Wall -Wextra -std=c++11
LDFLAGS = -rpath ~/.brew/lib
SRC = main.cpp \
			BinaryCall.cpp \
			Game/Game.cpp \
			Player/Player.cpp \
			Timer/Timer.cpp


OBJ = $(SRC:.cpp=.o)

all: sdl sfml $(NAME)


$(NAME): $(OBJ)
	$(COMPILATOR) $(FLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.cpp
	$(COMPILATOR) $(INC) -o $@ -c $< $(FLAGS)

clean:
	@rm -rf $(OBJ)
	@make clean -C ./lib/sdl
	@make clean -C ./lib/sfml

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C ./lib/sdl
	@make fclean -C ./lib/sfml

re: fclean all

install:
	@sh install.sh

assets:
	@mkdir -p assets
	@curl -o ./assets/scheme.pdf https://transfer.sh/uHJWo/scheme.pdf
	@curl -o ./assets/assets.zip https://transfer.sh/10vY6n/assets.zip
	@zip -d ./assets/assets.zip __MACOSX/\*
	@unzip ./assets/assets.zip
	@rm -rf  __MACOSX/\*
	@rm ./assets/assets.zip

aclean:
	@rm -rf assets schemes.pdf

dsclean:
	@rm -rf .DS_S*
	@rm -rf */.DS_S*

sdl:
	@make -C lib/sdl
	@make re -C ./lib/sdl
sfml:
	@make -C lib/sfml
	@make re -C ./lib/sfml

.PHONY : re fclean clean all install assets aclean dsclean sdl sfml
