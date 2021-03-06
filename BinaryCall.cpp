#include "main.hpp"

void    dlerror_wrapper(void) {
    std::cout << "\033[38;5;204mDynamic Library Error : \033[0m" << dlerror() << std::endl;
    throw Exception::Throw(LIB_FAIL);
}

bool    openBinaryLib(char *path) {
    if (!(BINARY_LIB = dlopen(path, RTLD_NOW))) {
        dlerror_wrapper();
        return false;
    }
    else
        return true;
}

bool    openBinaryAudio(void) {
    if (!(BINARY_AUDIO = dlopen("audio.so", RTLD_NOW | RTLD_NODELETE))) {
        dlerror_wrapper();
        return false;
    }
    else
        return true;
}

IGraphism   *createEngine(unsigned int width, unsigned int height, eDirection direction) {
    std::string symbol = "createWindow";
    IGraphism   *(*windowCreator)(unsigned int, unsigned int, eDirection);
    windowCreator = (IGraphism *(*)(unsigned int, unsigned int, eDirection)) dlsym(BINARY_LIB, symbol.c_str());

    if (!windowCreator)
        dlerror_wrapper();
    IGraphism *window = windowCreator(width, height, direction);
    return window;
}

void    deleteEngine(IGraphism *engine) {
    std::string symbol = "deleteWindow";
    void    (*engineDestructor)(IGraphism *);
    engineDestructor = (void (*)(IGraphism *)) dlsym(BINARY_LIB, symbol.c_str());
    if (!engineDestructor)
        dlerror_wrapper();
    engineDestructor(engine);
    return;
}

IEntity   *createEntity(unsigned int x, unsigned int y, eType type, eDirection direction, eTexture texture) {
    std::string symbol = "createEntity";
    IEntity   *(*entityCreator)(unsigned int, unsigned int, eType type, eDirection direction, eTexture texture);
    entityCreator = (IEntity *(*)(unsigned int, unsigned int, eType type, eDirection direction, eTexture texture)) dlsym(BINARY_LIB, symbol.c_str());
    if (!entityCreator)
        dlerror_wrapper();
    IEntity *entity = entityCreator(x, y, type, direction, texture);
    return entity;
}

void    deleteEntity(IEntity *entity) {
    std::string symbol = "deleteEntity";
    IEntity   *(*entityDestructor)(IEntity *);
    entityDestructor = (IEntity *(*)(IEntity *)) dlsym(BINARY_LIB, symbol.c_str());
    if (!entityDestructor)
        dlerror_wrapper();
    entityDestructor(entity);
    return;
}

ICoreAudio  *createCoreAudio(void) {
    std::string symbol = "newCoreAudio";
    ICoreAudio  *(*CoreAudioCreator)(void);
    CoreAudioCreator = (ICoreAudio *(*)(void)) dlsym(BINARY_AUDIO, symbol.c_str());
    if (!CoreAudioCreator)
        dlerror_wrapper();
    ICoreAudio *coreAudio = CoreAudioCreator();
    return coreAudio;
}

void    deleteCoreAudio(ICoreAudio *coreAudio) {
    std::string symbol = "deleteCoreAudio";
    ICoreAudio *(*CoreAudioDestructor)(ICoreAudio *);
    CoreAudioDestructor = (ICoreAudio *(*)(ICoreAudio *)) dlsym(BINARY_AUDIO, symbol.c_str());

    if (!CoreAudioDestructor)
      dlerror_wrapper();
    CoreAudioDestructor(coreAudio);
    return;
}
