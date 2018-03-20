#ifndef WINDOWALLEGRO_HPP
# define WINDOWALLEGRO_HPP


# include <iostream>

# include <allegro5/allegro.h>
# include <allegro5/allegro_image.h>
# include <map>

# include "IGraphism.hpp"
# include "IEntity.hpp"


class Window  : public IGraphism {
private:
  Window(void);

  void            drawFrame(std::list <IEntity *> data) const;
  // void            drawMenu(int lives) const;
  eHook           getHooks(void) const;
  void            setHooks(void);
  unsigned int    getWidth(void) const;
  unsigned int    getHeight(void) const;
  // void            initTextures(void);
  // GLuint          loadBMP(const char * imagepath) const;
public:
  Window(unsigned int width, unsigned int height);
  ~Window(void);
  eHook                               hook;
  eHook                               engine;
  unsigned int                        wWidth;
  unsigned int                        wHeight;
  ALLEGRO_DISPLAY                     *pWindow;
  ALLEGRO_EVENT_QUEUE                 *pQueue;
  // sf::Font                            pFont;
  // std::map <eTexture,  GLuint>   _textures;


};

extern "C" {
    Window              *createWindow(unsigned int width, unsigned int height);
    void                 deleteWindow(Window *window);
}

#endif
