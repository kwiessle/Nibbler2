#include "main.hpp"
#include "Game.hpp"

int   main(int ac, char **av) {
  void    *dl_handle;


  switch (ac) {
    case 0:
    case 1:
    case 2:
    case 3: break;
    case 4: {
      unsigned int width = atoi(av[1]);
      unsigned int height = atoi(av[2]);
      char *path = av[3];


      if (!(dl_handle = dlopen(path, RTLD_LOCAL | RTLD_LAZY))) {
        dlerror_wrapper();
      }
      else {
        IGraphism *engine = createEngine(dl_handle, width, height);
        // Game game = Game::singleton();
        Game *game = new Game(engine, dl_handle);
        // Game::singleton();
        // Game::singleton().setBinaryLib(dl_handle);
        // Game::singleton().setEngine(engine);
        // Game::singleton().play();
        game->play();
        deleteEngine(dl_handle, engine);
      }


    }
  }




  return 0;
}
