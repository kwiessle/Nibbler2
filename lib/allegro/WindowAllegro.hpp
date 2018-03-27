#ifndef WINDOWALLEGRO_HPP
# define WINDOWALLEGRO_HPP

# define ALLEGRO_NO_MAGIC_MAIN
# include <allegro5/allegro.h>
# include <allegro5/allegro_image.h>
# include "IGraphism.hpp"
# include "IEntity.hpp"


class Window  : public IGraphism {
private:
  Window(void);

  void            drawFrame(std::list <IEntity *> data, int lives, int score) const;
  bool            displayPause(int status);
  // void            drawMenu(int lives) const;
  eHook           getHooks(void) const;
  eHook           getStatus(void) const;
  void            changeHook(eHook status);

  void            setStatus(eHook status) ;
  eEngine         getEngine(void) const;
  bool            engineHasChanged(void) const;
  bool              hookHasChanged(void) const;
  void             reverseHookChecker(void);
  void            setHooks(void);
  unsigned int    getWidth(void) const;
  unsigned int    getHeight(void) const;
  int              maintest(int ac, char **av);
  // void            initTextures(void);
  // GLuint          loadBMP(const char * imagepath) const;
public:
  Window(unsigned int width, unsigned int height, eHook hook);
  ~Window(void);
  eHook                               hook;
  eHook                               status;
  eEngine                             engine;
  bool                                engineChecker;
  bool                                hookChecker;
  unsigned int                        wWidth;
  unsigned int                        wHeight;
  ALLEGRO_DISPLAY                     *pWindow;
  ALLEGRO_EVENT_QUEUE                 *pQueue;
  // sf::Font                            pFont;
  // std::map <eTexture,  GLuint>   _textures;


};

extern "C" {
    Window              *createWindow(unsigned int width, unsigned int height, eHook hook);
    void                 deleteWindow(Window *window);
}

#endif
