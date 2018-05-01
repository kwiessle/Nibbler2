#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include "IGraphism.hpp"


class Window : public IGraphism {
  private:
    Window(void);
    Window(Window const &src);

    Window  &operator=(Window const &rhs);

    void              drawFrame(std::list <IEntity *> data, int lives, int score) const;
    bool              displayPause(int score, int bestScore);
    void              drawMenu(int lives, int score) const;
    void              initTextures(void);

    void              handleEvent(int milliseconds);
    void              handlePauseEvent(SDL_Event event);

    eDirection        getDirection(void) const;
    void              setDirection(SDL_Event event);
    void              updateDirection(eDirection direction);
    bool              directionHasChanged(void) const;
    void              reverseDirectionChecker(void);

    eStatus           getStatus(void) const;
    void              setStatus(SDL_Event event);
    void              updateStatus(eStatus status);

    void              setEngine(SDL_Event event);
    eEngine           getEngine(void) const;
    bool              engineHasChanged(void) const;
    void              setEngineChange(bool status);

    unsigned int      getWidth(void) const;
    unsigned int      getHeight(void) const;
  public:
    Window(unsigned int width, unsigned int height, eDirection direction);
    ~Window(void);

    eDirection                          direction;
    eStatus                             status;
    eEngine                             engine;
    bool                                engineChecker;
    bool                                directionChecker;
    unsigned int                        wWidth;
    unsigned int                        wHeight;
    SDL_Window                          *pWindow;
    SDL_Renderer                        *pRenderer;
    TTF_Font                            *pFont;
    std::map <eTexture, SDL_Surface *>  _textures;

};

extern "C" {
  Window              *createWindow(unsigned int width, unsigned int height, eDirection direction);
  void                 deleteWindow(Window *window);
}

#endif
