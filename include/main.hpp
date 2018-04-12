#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <dlfcn.h>
# include "IGraphism.hpp"
# include "IEntity.hpp"
# include "Exception.hpp"
# include <list>

extern void *BINARY_LIB;

class Game;

IGraphism   *createEngine(
    unsigned int width,
    unsigned int height,
    eDirection hook
);

IEntity     *createEntity(
    unsigned int x,
    unsigned int y,
    eType type,
    eDirection direction,
    eTexture texture
);

bool        openBinaryLib(char *path);
void        deleteEngine(IGraphism *engine);
void        deleteEntity(IEntity *entity);
void        dlerror_wrapper(void);


#endif