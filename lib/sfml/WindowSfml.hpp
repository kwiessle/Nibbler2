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

    int         getHooks(void) const;
    void        drawFrame(std::list <IEntity *> data) const;

  public:
    Window(unsigned int width, unsigned int height);
    ~Window(void);

    sf::RenderWindow	*window;

};

extern "C" {
  Window              *createWindow(unsigned int width, unsigned int height);
  void                 deleteWindow(Window *window);
}

#endif
