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

    void                drawFrame(std::list <IEntity *> data, int lives, int score) const;
    bool                displayPause(int status);
    void                drawMenu(int lives, int score) const;
    void                initTextures(void);

    void                handleEvent(void);
    void                handlePauseEvent(sf::Event event);
    eDirection          getDirection(void) const;
    void                setDirection(sf::Event event);
    void                updateDirection(eDirection direction);
    bool                directionHasChanged(void) const;
    void                reverseDirectionChecker(void);

    eStatus             getStatus(void) const;
    void                setStatus(sf::Event event);
    void                updateStatus(eStatus status);

    void                setEngine(sf::Event event);
    eEngine             getEngine(void) const;
    bool                engineHasChanged(void) const;

    unsigned int        getWidth(void) const;
    unsigned int        getHeight(void) const;
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
    sf::RenderWindow                    *window;
    sf::Font                            pFont;
    std::map <eTexture,  sf::Texture>   _textures;


};

extern "C" {
  Window              *createWindow(unsigned int width, unsigned int height, eDirection direction);
  void                 deleteWindow(Window *window);
}

#endif
