#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <dlfcn.h>
# include "IGraphism.hpp"
# include "IEntity.hpp"
# include <list>

extern void *BINARY_LIB;

class Game;

IGraphism   *createEngine(
  void *dl_handle,
  unsigned int width,
  unsigned int height
);

IEntity     *createEntity(
  void *dl_handle,
  unsigned int x,
  unsigned int y,
  eType type,
  eDirection direction,
  eTexture texture
);

void        deleteEngine(void *dl_handle, IGraphism *engine);
void        dlerror_wrapper(void);


#endif
