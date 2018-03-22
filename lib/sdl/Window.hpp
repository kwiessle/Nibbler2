#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <iostream>
# include "IGraphism.hpp"
# include <map>


class Window : public IGraphism {
  private:
    Window(void);

    void              setHooks(void);
    eHook             getHooks(void) const;
    eHook             getStatus(void) const;
    void            setStatus(eHook status);

    eEngine           getEngine(void) const;
    bool              engineHasChanged(void) const;
    void              drawFrame(std::list <IEntity *> data, int lives, int score) const;
    bool              displayPause(int status);
    void              drawMenu(int lives, int score) const;
    unsigned int      getWidth(void) const;
    unsigned int      getHeight(void) const;
    void              initTextures(void);
  public:
    Window(unsigned int width, unsigned int height, eHook hook);
    ~Window(void);

    SDL_Window        *pWindow;
    SDL_Renderer      *pRenderer;
    TTF_Font          *pFont;
    unsigned int      wWidth;
    unsigned int      wHeight;
    eHook             hook;
    eHook             status;
    eEngine           engine;
    bool              engineChecker;


    std::map <eTexture, SDL_Surface *>      _textures;

};

extern "C" {
  Window              *createWindow(unsigned int width, unsigned int height, eHook hook);
  void                 deleteWindow(Window *window);
}

#endif
