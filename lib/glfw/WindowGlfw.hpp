#ifndef WINDOWOPENGL_HPP
# define WINDOWOPENGL_HPP

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <GL/freeglut.h>
# include "IGraphism.hpp"
# include "IEntity.hpp"
# include "Exception.hpp"


class Window  : public IGraphism {
  private:
    Window(void);

    void            drawFrame(std::list <IEntity *> data, int lives, int score) const;
    void            displayTextures(std::list <IEntity *>::iterator iter) const;
    bool            displayPause(int score);
    void            drawMenu(int lives, int score) const;
    void            initTextures(void);
    GLuint          loadBMP(const char * imagepath) const;

    void            handleEvent(void);
    void            handlePauseEvent(void);
    eDirection      getDirection(void) const;
    void            setDirection(void);
    void            updateDirection(eDirection direction);
    bool            directionHasChanged(void) const;
    void            reverseDirectionChecker(void);

    eStatus         getStatus(void) const;
    void            setStatus(void);
    void            updateStatus(eStatus status);

    void            setEngine(void);
    eEngine         getEngine(void) const;
    bool            engineHasChanged(void) const;

    unsigned int    getWidth(void) const;
    unsigned int    getHeight(void) const;
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
    GLFWwindow                          *pWindow;
    // sf::Font                            pFont;
    GLuint                              _textures[23];


};

extern "C" {
Window              *createWindow(unsigned int width, unsigned int height, eDirection direction);
void                 deleteWindow(Window *window);
}

#endif
