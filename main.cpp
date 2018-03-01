#include <dlfcn.h>
#include <iostream>
#include "IGraphism.hpp"

void  dlerror_wrapper(void) {
  std::cout << "Error: " << dlerror() << std::endl;
}

IGraphism   *openLibrary(void *dl_handle, char const *symbol, unsigned int width, unsigned int height) {

  if (!dl_handle) {
    dlerror_wrapper();
  }
  IGraphism   *(*windowCreator)(unsigned int, unsigned int);
  windowCreator = (IGraphism *(*)(unsigned int, unsigned int)) dlsym(dl_handle, symbol);
  if (!windowCreator)
    dlerror_wrapper();
  IGraphism *window = windowCreator(width, height);
  return window;
}

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
      std::string  symbol = "createWindow";
      char *path = av[3];

      dl_handle = dlopen(path, RTLD_LOCAL | RTLD_LAZY);
      IGraphism *engine = openLibrary(dl_handle, symbol.c_str(), width, height);
      engine->loop();

    }
  }




  return 0;
}
