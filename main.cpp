#include "main.hpp"
#include "Game.hpp"

void *BINARY_LIB;
void *BINARY_AUDIO;

int     handleMode(char *string) {
    std::string flag = "--hardcore";
    if (string && string == flag)
        return 1;
    if (string && string != flag)
        throw Exception::Throw(USAGE);
    return 0;
}
void    handleParameters(unsigned int width, unsigned int height) {

    if (width < 15 || width > 55) {
        throw Exception::Throw(SIZE);
    }
    if (height < 15 || height > 30) {
        throw Exception::Throw(SIZE);
    }
}

int      main(int ac, char **av) {
    try {
        switch (ac) {
            case 4:
            case 5: {
                unsigned int width = atoi(av[1]);
                unsigned int height = atoi(av[2]);
                handleParameters(width, height);
                int mode = handleMode(av[4]);
                char *path = av[3];
                if (!openBinaryLib(path) || !openBinaryAudio()) {
                    throw Exception::Throw(LIB_FAIL);
                }
                else
                    Game::singleton().start(width, height, mode);
                break;
            }
            default: throw Exception::Throw(USAGE);
        }
    }
    catch (Exception::GraphicalException &e) {
     std::cout << e.what() << std::endl;
    }
    catch (Exception::GameException &e) {
     std::cout << e.what() << std::endl;
    }
    return 0;
}
