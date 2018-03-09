#include "main.hpp"



 void  dlerror_wrapper(void) {
  std::cout << "Error: " << dlerror() << std::endl;
}

bool   openBinaryLib(char *path) {
    if (!(BINARY_LIB = dlopen(path, RTLD_LAZY | RTLD_LOCAL))) {
      dlerror_wrapper();
      return false;
    }
    else {return true;}
}

IGraphism   *createEngine(unsigned int width, unsigned int height) {
  std::string symbol = "createWindow";
  IGraphism   *(*windowCreator)(unsigned int, unsigned int);
  windowCreator = (IGraphism *(*)(unsigned int, unsigned int)) dlsym(BINARY_LIB, symbol.c_str());

  if (!windowCreator)
    dlerror_wrapper();

  IGraphism *window = windowCreator(width, height);
  return window;
}

void      deleteEngine(IGraphism *engine) {
  std::string symbol = "deleteWindow";
  void      (*engineDestructor)(IGraphism *);
  engineDestructor = (void (*)(IGraphism *)) dlsym(BINARY_LIB, symbol.c_str());

  if (!engineDestructor)
    dlerror_wrapper();

  engineDestructor(engine);
  return;
}

IEntity   *createEntity(unsigned int x, unsigned int y, eType type, eHook direction, eTexture texture) {
  std::string symbol = "createEntity";
  IEntity   *(*entityCreator)(unsigned int, unsigned int, eType type, eHook direction, eTexture texture);
  entityCreator = (IEntity *(*)(unsigned int, unsigned int, eType type, eHook direction, eTexture texture)) dlsym(BINARY_LIB, symbol.c_str());
  if (!entityCreator)
    dlerror_wrapper();

  IEntity *entity = entityCreator(x, y, type, direction, texture);
  return entity;
}

void      deleteEntity(IEntity *entity) {
  std::string symbol = "deleteEntity";
  IEntity   *(*entityDestructor)(IEntity *);
  entityDestructor = (IEntity *(*)(IEntity *)) dlsym(BINARY_LIB, symbol.c_str());

  if (!entityDestructor)
    dlerror_wrapper();

  entityDestructor(entity);
  return;
}
