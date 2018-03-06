#include "main.hpp"
#include "Game.hpp"

void *BINARY_LIB;

int   main(int ac, char **av) {
  // void    *dl_handle;


  switch (ac) {
    case 0:
    case 1:
    case 2:
    case 3: break;
    case 4: {
      unsigned int width = atoi(av[1]);
      unsigned int height = atoi(av[2]);
      char *path = av[3];


      if (!(BINARY_LIB = dlopen(path, RTLD_LOCAL | RTLD_LAZY))) {
        dlerror_wrapper();
      }
      else {


         Game::singleton().start(width, height);
        // Game::singleton().refresh();

        ;
        // deleteEngine(BINARY_LIB, Game::singleton.getEngine());
      }


    }
  }




  return 0;
}
