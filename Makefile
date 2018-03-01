NAME = Nibbler
COMPILATOR = clang++
INC	= -I . -I IGraphism
FLAGS = -Werror -Wall -Wextra -std=c++11

SRC = main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILATOR) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(COMPILATOR) $(INC) -o $@ -c $< $(FLAGS)

clean:
	@rm -rf $(OBJ)
	@make fclean -C IGraphism/sdl

fclean: clean
	@rm -rf $(NAME)

re: fclean all

install:
	@sh install.sh

scheme:
	@mkdir -p assets
	@curl -o ./schemes.pdf http://dl.free.fr/mfMBHqNAf
	@mv schemes.pdf assets

assets:
	@mkdir -p assets
	@curl -o ./assets.zip http://dl.free.fr/q6Q35FrKf
	@unzip assets.zip -d assets
	@rm assets.zip

aclean:
	@rm -rf assets schemes.pdf

dsclean:
	@rm -rf */.DS_S*

sdl:
	@make -C IGraphism/sdl


.PHONY : re fclean clean all install assets aclean dsclean scheme sdl
