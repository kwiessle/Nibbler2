#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <dlfcn.h>
# include "IGraphism.hpp"
# include "IEntity.hpp"
# include "ICoreAudio.hpp"
# include "Exception.hpp"
# include <list>

extern void *BINARY_LIB;
extern void *BINARY_AUDIO;

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

ICoreAudio  *createCoreAudio(void);


bool        openBinaryLib(char *path);
bool        openBinaryAudio(void);
void        deleteEngine(IGraphism *engine);
void        deleteEntity(IEntity *entity);
void        deleteCoreAudio(ICoreAudio *coreCoreAudio);
void        dlerror_wrapper(void);


#endif
