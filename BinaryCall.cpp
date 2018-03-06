#include "main.hpp"



 void  dlerror_wrapper(void) {
  std::cout << "Error: " << dlerror() << std::endl;
}

IGraphism   *createEngine(void *dl_handle, unsigned int width, unsigned int height) {
  std::string symbol = "createWindow";
  IGraphism   *(*windowCreator)(unsigned int, unsigned int);
  windowCreator = (IGraphism *(*)(unsigned int, unsigned int)) dlsym(dl_handle, symbol.c_str());

  if (!windowCreator)
    dlerror_wrapper();
  IGraphism *window = windowCreator(width, height);
  return window;
}

void      deleteEngine(void *dl_handle, IGraphism *engine) {
  std::string symbol = "deleteWindow";
  void      (*engineDestructor)(IGraphism *);
  engineDestructor = (void (*)(IGraphism *)) dlsym(dl_handle, symbol.c_str());

  if (!engineDestructor)
    dlerror_wrapper();
  engineDestructor(engine);
  return;
}

IEntity   *createEntity(void *dl_handle, unsigned int x, unsigned int y, eType type, eDirection direction, eTexture texture) {
  std::string symbol = "createEntity";
  IEntity   *(*entityCreator)(unsigned int, unsigned int, eType type, eDirection direction, eTexture texture);
  entityCreator = (IEntity *(*)(unsigned int, unsigned int, eType type, eDirection direction, eTexture texture)) dlsym(dl_handle, symbol.c_str());
  if (!entityCreator)
    dlerror_wrapper();
  IEntity *entity = entityCreator(x, y, type, direction, texture);
  return entity;
}
