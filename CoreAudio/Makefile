NAME = ../audio.so
COMPILATOR = clang++
FLAGS = -Werror -Wall -Wextra -std=c++11
INC	=  -I ../include -I ~/.brew/include
AUDIO = -fPIC -shared
AUDIO +=  -L ~/.brew/lib/ -lSDL2 -lSDL2_MIXER


SRC = CoreAudio.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "🔊 \033[33;1m[SDL_MIXER]\033[0m dylib compiled"
	@$(COMPILATOR) $(AUDIO) $(OBJ) -o $(NAME)

%.o: %.cpp
	@$(COMPILATOR) $(INC) -o $@ -c $< $(FLAGS)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : re fclean clean all
