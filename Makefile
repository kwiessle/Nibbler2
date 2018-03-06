NAME = Nibbler
LOGIN = kwiessle/vquesnel
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

scheme:
	@mkdir -p assets
	@curl -o ./scheme.pdf https://transfer.sh/uHJWo/scheme.pdf
	@mv scheme.pdf assets

assets:
	@mkdir -p assets
	@curl -o ./assets.zip https://transfer.sh/ajM1s/assets.zip
	@unzip assets.zip -d assets
	@rm assets.zip

aclean:
	@rm -rf assets schemes.pdf

.PHONY : re fclean clean all
