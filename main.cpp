#include "main.hpp"
#include "Game.hpp"

void *BINARY_LIB;

int   main(int ac, char **av) {
  switch (ac) {
    case 0:
    case 1:
    case 2:
    case 3: break;
    case 4:
    case 5: {
      unsigned int width = atoi(av[1]);
      unsigned int height = atoi(av[2]);
      std::cout << "hello" <<std::endl;
      std::string flag = "--hardcore";
      int mode = 0;
      char *path = av[3];
      if (!openBinaryLib(path)) { std::cout << "Binary Call failed" << std::endl;}
      else {
          if (av[4] && av[4] == flag)
            mode = 1;
         Game::singleton().start(width, height, mode);
      }
    }
  }
  return 0;
}
