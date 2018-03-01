NAME = Nibbler
COMPILATOR = clang++
INC	= -I . -I avm -I parser -I instruction -I data -I exceptions
FLAGS = -Werror -Wall -Wextra -std=c++11

SRC =

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILATOR) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(COMPILATOR) $(INC) -o $@ -c $< $(FLAGS)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

install:
	@sh install.sh

schemes:
	@curl -o ./schemes.pdf http://dl.free.fr/mfMBHqNAf

assets:
	@mkdir assets
	@curl -o ./assets.zip http://dl.free.fr/q6Q35FrKf
	@unzip assets.zip -d assets
	@rm assets.zip

aclean:
	@rm -rf assets schemes.pdf

.PHONY : re fclean clean all
