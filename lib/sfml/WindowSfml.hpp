#ifndef SWINDOW_HPP
# define SWINDOW_HPP

# include <SFML/System.hpp>
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include <iostream>
# include "IGraphism.hpp"

class Window : public IGraphism {
  private:
    Window(void);

    void        drawFrame(std::list <IEntity *> data) const;
    eHook       getHooks(void) const;
    void        setHooks(void);
    unsigned int      getWidth(void) const;
    unsigned int      getHeight(void) const;
    void              initTextures(void);
  public:
    Window(unsigned int width, unsigned int height);
    ~Window(void);
    eHook        hook;
    unsigned int      wWidth;
    unsigned int      wHeight;
    sf::RenderWindow	*window;
    std::map <eTexture,  sf::Texture>      _textures;


};

extern "C" {
  Window              *createWindow(unsigned int width, unsigned int height);
  void                 deleteWindow(Window *window);
}

#endif